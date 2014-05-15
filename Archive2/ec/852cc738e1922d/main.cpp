#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
 
int main(void)
{
    printf("exp2(1.0)        = %.1f\n", exp2(1.0));
    printf("log2(2.0)        = %.1f\n", log2(2.0));   /* inverse of exp2 */
    printf("exp2(+0.0)       = %.1f\n", exp2(+0.0));
    printf("exp2(-0.0)       = %.1f\n", exp2(-0.0));
    printf("exp2(+INFINITY)  = %.1f\n", exp2(+INFINITY));
    printf("exp2(-INFINITY)  = %.1f\n", exp2(-INFINITY));
    printf("exp2(NAN)        = %.1f\n", exp2(NAN));
    printf("\n");
 
    /* inf but no range error */
    errno = 0;
    printf("exp2(1024.0)     = %f\n", exp2(1024.0));
    printf("%s\n",strerror(errno));
 
    /* range error */
    errno = 0;
    printf("exp2(1025.0)     = %f\n", exp2(1025.0));
    printf("%s\n",strerror(errno));
 
    return 0;
}