#include <dirent.h>    /* opendir() */
#include <fcntl.h>     /* open() */
#include <stdio.h>     /* perror() */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <string.h>    /* strstr() */
#include <sys/stat.h>  /* open() */
#include <sys/types.h> /* opendir() */
#include <unistd.h>    /* read() */

int
main (int   argc __attribute__((__unused__)),
      char**argv __attribute__((__unused__)))
{
    DIR* folder;
    int fileDescriptor;
    ssize_t len;
    folder = opendir(".");
    if (!folder) {
        perror("opendir()");
        return EXIT_FAILURE;
    }
    struct dirent* entry;
    char buf[256];
    for (entry = readdir(folder); entry; entry = readdir(folder)) {
        if (strstr(entry->d_name, ".txt")) {
            if (strlen(entry->d_name) >= sizeof(buf)) {
                fprintf(stderr,
                        "the filename is too large: %ld bytes (only %ld bytes available)",
                        strlen(entry->d_name) + 1, sizeof(buf));
                return EXIT_FAILURE;
            }
            strcpy(buf, entry->d_name);

            fileDescriptor = open(buf, O_RDONLY);
            len = read(fileDescriptor, buf, sizeof(buf));
            if (((size_t)len) >= sizeof(buf)) {
                fprintf(stderr,
                        "the buffer is too small for the file: %ld bytes (increase to %ld)",
                        sizeof(buf), sizeof(buf) << 1);
                return EXIT_FAILURE;
            }
            write(fileno(stdout), "(c)found: ", strlen("(c)found: "));
            write(fileno(stdout), buf, len);
            sync();
            if (0 > close(fileDescriptor)) {
                perror("close()");
                return EXIT_FAILURE;
            }
        }
    }
    closedir(folder);

    return EXIT_SUCCESS;
}

