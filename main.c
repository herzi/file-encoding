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

	return EXIT_SUCCESS;
}
