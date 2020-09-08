/* mimefilter - list files from on stdin that match any MIME types given as arguments */
#define _POSIX_C_SOURCE 200809L
#include <err.h>
#include <fnmatch.h>
#include <limits.h>
#include <magic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

void
usage(const char *me)
{
	fprintf(stderr, "usage: ... | %s [-!0v] mime/type...\n", me);
	exit(EX_USAGE);
}

int
main(int argc, char *argv[])
{
	int opt;
	int inverse = 0;
	char delimiter = '\n';
	int v = 0;
	while ((opt = getopt(argc, argv, "!0v")) != -1) {
		switch (opt) {
		case '!':
			inverse = 1;
			break;
		case '0':
			delimiter = '\0';
			break;
		case 'v':
			v = 1;
			break;
		default:
			usage(argv[0]);
		}
	}

	if (optind >= argc) usage(argv[0]);

	/* Ask libmagic(3) to only give us the mime/type,
	 * and treat OS errors as real errors. */
	magic_t cookie = magic_open(MAGIC_MIME_TYPE | MAGIC_ERROR);
	if (magic_load(cookie, NULL) != 0)
		err(EX_UNAVAILABLE, "libmagic error: %s\n", magic_error(cookie));

	char *file = NULL;
	size_t size = 0;
	const char *mime;

	int read;
	/* Receive list of files on stdin. */
	while ((read = getdelim(&file, &size, delimiter, stdin)) != -1) {
		if (file[read - 1] == delimiter) file[read - 1] = 0;

		if (v) fprintf(stderr, "%s: reading `%s'\n", argv[0], file);

		/* Get MIME of file... */
		if (!(mime = magic_file(cookie, file))) {
			errx(EX_UNAVAILABLE, "libmagic error: %s", magic_error(cookie));
			return EX_UNAVAILABLE;
		}

		/* Check against MIME types given in arguments. */
		for (int i = 1; i < argc; i++) {
			/* glob the requested type against the file's type */
			int matched = fnmatch(argv[i], mime, FNM_PATHNAME);
			if (matched == FNM_NOMATCH && inverse == 1) {
				if (v)
					fprintf(
					    stderr,
					    "%s: file `%s': `%s'\n",
					    argv[0],
					    file,
					    mime
					);
				printf("%s%c", file, delimiter);
			}
		}
	}
	return 0;
}
