#include <stdio.h>
#include <string.h>

int main(void)
{
    char s1[32] = "cat"; // NB: s1 needs to be large enough to hold additional chars !
    char s2[32] = "hsklsdksdhkjadsfhjkld";   

    strncat(s1, &s2[1], 1);

    printf("s1 is now %s\n", s1);

    return 0;
}
