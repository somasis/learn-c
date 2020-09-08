/* contains printf(). */
#include <stdio.h>

/* main() must always return an integer.
 * if my program weren't taking any arguments, I could just say
 * int main()
 * but, in order to take command line arguments, you need argc and argv.
 * argc is the number of strings (argument count),
 * argv is the set of arguments (argument vector).
 * the names don't matter, it's just that if main() is given any arguments, it'll end up in those.
 */

int main(){
	printf("ma ale o, toki a\n");

	/* There's no need for a return here. In C99, return can be omitted in main(), as there is an
	 * implicit `return 0`.
	 */
}

