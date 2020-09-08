CC = clang
LD = ld.lld

BINS = \
    hello \
    mimefilter

CFLAGS += -std=c99 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -O2

mimefilter: LDFLAGS += -lmagic

# dev: all check

all: ${BINS}

# check: ${BINS}
# 	for bin in ${BINS}; do valgrind -q ./$${bin}; done

watch:
	# while :; do git ls-files | rwc -p | xe -s 'make'; done

watch-mimefilter:
	rwc -p *.[ch] Makefile \
	    | xe -s ' \
	        set -x; \
	        clear; \
	        make \
	            && echo ~/audio/library/9\ Lazy\ 9\ -\ Electric\ Lazyland\ \(1994\)/01\ -\ 9\ Lazy\ 9\ -\ Life\ Goes\ On\ \&\ On.opus; echo $?; exit 0'

clean:
	rm -f ${BINS}
