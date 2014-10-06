#include <stdio.h>

int main(void) {
    const char c = 'c';
	printf( "%c", c);
    char* pc;
    const char** pcc = &pc;   // not allowed (thankfully!)
                //^^^ here the bundit is hidden under const: "I will not modify"
    *pcc = &c;                // *pcc is "pointer to const" right? so this is allowed...
    *pc = 'C';                // would allow to modify a const object, *pc is char right?
    printf( "%c", c);
	return 0;
}
