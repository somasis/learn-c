#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

void usage() {
	char *usage = "usage: repo-list [-lp]";
	fprintf(stderr, "%s\n", usage);

	exit(EX_USAGE);
}

int main(int argc, char *argv[]) {
	int arg;
	char type = 'a';

	/* getopt(3) says...
	 *     If there are no more option characters, getopt() returns -1.  Then
	 *     optind is the index in argv of the first argv-element that is not an
	 *     option.
	 */
	while ((arg = getopt(argc, argv, "lp")) != -1) {
		switch (arg) {
			case 'l':
				type = 'l';
				break;
			case 'p':
				type = 'p';
				break;
			default: /* unknown argument */
				usage();
		}
	}

	fprintf(stderr, "type: %c\n", type);

}

/*
libraries_only=false
packages_only=false

while getopts :lp arg >/dev/null 2>&1; do
    case "${arg}" in
        l)
            libraries_only=true
            ;;
        p)
            packages_only=true
            ;;
        ?)
            error "unknown argument -- ${OPTARG}"
            myusage
            ;;
    esac
done
shift $((OPTIND - 1))

cd "@@dbdir@@/repositories" ||
    die 2 "repositories directory '@@dbdir@@' does not exist"

for repo in *; do
    [ -d "${repo}" ] || continue
    case "${repo}" in .*) continue ;; esac

    "${libraries_only}" && ! [ -d "${repo}"/libraries ] && continue
    "${packages_only}" && ! [ -d "${repo}"/packages ] && continue

    [ -r "${repo}"/metadata/priority ] &&
        printf '%s:%s\n' "$(cat "${repo}"/metadata/priority)" "${repo}"
done | sort -t: -k 1n | cut -d: -f2-
*/
