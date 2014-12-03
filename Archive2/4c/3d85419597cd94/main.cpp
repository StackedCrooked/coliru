#include <stdio.h>
#include <string.h>
 
int main(void)
{
    char a1[] = {'a', 'b', 'c'};
    char a2[] = {'a', 'b', 'd'};
 
    printf("'abc' vs 'abd': %2d\n", memcmp(a1, a2, sizeof a1));
    printf("'abd' vs 'abc': %2d\n", memcmp(a2, a1, sizeof a1));
    printf("'abc' vs 'abc': %2d\n", memcmp(a1, a1, sizeof a1));
 
    return 0;
}