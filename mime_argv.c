#include <stdlib.h>
#include <sysexits.h>
#include <string.h>
#include <fnmatch.h>
#include <stdio.h>
#include <magic.h>

int main(const int argc, const char *argv[]) {
	magic_t cookie = magic_open(MAGIC_MIME_TYPE | MAGIC_ERROR);
	if (magic_load(cookie, NULL) != 0) fprintf(stderr, "magic error: %s\n", magic_error(cookie));

	const char * want_mime = argv[1];
	// fprintf(stderr, "want: %s\n", want_mime);

	const char * file_mime;
	for (int i = 2; i < argc; i++) {
		// fprintf(stderr, "mime: %s\n", argv[i]);

		if (!(file_mime = magic_file(cookie, argv[i]))) {
			// fprintf(stderr, "magic error: %s\n", magic_error(cookie));
			return EX_UNAVAILABLE;
		}

		if (fnmatch(want_mime, file_mime, FNM_PATHNAME) == 0)
			puts(argv[i]);
	}
	return 0;
}
