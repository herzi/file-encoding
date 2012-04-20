#include <dirent.h>    /* opendir() */
#include <fcntl.h>     /* creat() */
#include <stdio.h>     /* perror() */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <string.h>    /* strlen() */
#include <sys/types.h> /* creat() */
#include <sys/stat.h>  /* creat() */
#include <unistd.h>    /* write() */

int
main (int   argc __attribute__((__unused__)),
      char**argv __attribute__((__unused__)))
{
    int fileDescriptor;
    char* ascii = "ASCII\n";
    char* iso88591 = "ISO-8859-1\n";
    char* utf8 = "UTF-8\n";
    size_t len;

    fileDescriptor = creat("halloe.txt", 0644);
    if (fileDescriptor < 0) {
        perror("creat(ascii)");
        return EXIT_FAILURE;
    }
    len = write(fileDescriptor, ascii, strlen(ascii));
    if (len != strlen(ascii)) {
        perror("write(ascii)");
        return EXIT_FAILURE;
    }
    if (close(fileDescriptor) < 0) {
        perror("close(ascii)");
        return EXIT_FAILURE;
    }

    fileDescriptor = creat("hall\xf6.txt", 0644);
    if (fileDescriptor < 0) {
        perror("creat(iso88591)");
        return EXIT_FAILURE;
    }
    len = write(fileDescriptor, iso88591, strlen(iso88591));
    if (len != strlen(iso88591)) {
        perror("write(iso88591)");
        return EXIT_FAILURE;
    }
    if (close(fileDescriptor) < 0) {
        perror("close(iso88591)");
        return EXIT_FAILURE;
    }

    fileDescriptor = creat("hall\xc3\xb6.txt", 0644);
    if (fileDescriptor < 0) {
        perror("creat(utf8)");
        return EXIT_FAILURE;
    }
    len = write(fileDescriptor, utf8, strlen(utf8));
    if (len != strlen(utf8)) {
        perror("write(utf8)");
        return EXIT_FAILURE;
    }
    if (close(fileDescriptor) < 0) {
        perror("close(utf8)");
        return EXIT_FAILURE;
    }

    DIR* folder;
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
            if (len >= sizeof(buf)) {
                fprintf(stderr,
                        "the buffer is too small for the file: %ld bytes (increase to %ld)",
                        sizeof(buf), sizeof(buf) << 1);
                return EXIT_FAILURE;
            }
            write(fileno(stdout), "found: ", strlen("found "));
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
