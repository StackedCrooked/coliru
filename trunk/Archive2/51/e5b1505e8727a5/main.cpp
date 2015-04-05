#include <stdio.h>
int main(void)
{
    float d;
    int rc = sscanf("1.2P", "%FP", &d);
    printf("scanf processed %d fields, d = %f\n", rc, d);
}
