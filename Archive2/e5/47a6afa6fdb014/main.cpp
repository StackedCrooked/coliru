#include <cstdio>

int main(void) {
    int blah = 5;
	blah > 6 ? printf("blah") : ({
								 printf("hello\n");
								 printf("there\n");
								 printf("win\n");
								});
	return 0;
}
