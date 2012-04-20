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
	struct {
		char* code;
		char* file;
	} tests[] = {
		{
			"Escaped\n", "hall%F6.txt"
		}, {
			"ASCII\n", "halloe.txt"
		}, {
			"ISO-8859-1\n", "hall\xf6.txt"
		}, {
			"UTF-8\n", "hall\xc3\xb6.txt"
		}
	};
    int fileDescriptor;
    ssize_t len;
	size_t i;

	for (i = 0; i < sizeof(tests) / sizeof(*tests); i++) {
		fileDescriptor = creat(tests[i].file, 0644);
		if (fileDescriptor < 0) {
			perror("creat()");
			return EXIT_FAILURE;
		}
		len = write(fileDescriptor, tests[i].code, strlen(tests[i].code));
		if (len < 0 || ((size_t)len) != strlen(tests[i].code)) {
			perror("write()");
			return EXIT_FAILURE;
		}
		if (close(fileDescriptor) < 0) {
			perror("close()");
			return EXIT_FAILURE;
		}
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
