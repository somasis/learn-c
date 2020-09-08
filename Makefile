BINS = \
    hello \
    repo-list

CFLAGS += -std=c99 -Wall -Wextra -Wpedantic -Wshadow -O2 -Werror

dev: all check

all: ${BINS}

check: ${BINS}
	for bin in ${BINS}; do valgrind -q ./$${bin}; done

clean:
	rm -f ${BINS}
