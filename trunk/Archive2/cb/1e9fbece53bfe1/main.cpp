#include <stdio.h>
union p                                                                                                                                
{
    int x;
    float y;
};
int main()
{
    union p p; 
    p.x = 0x42200000;
    printf("%f\n", p.y);
    printf("%d\n", p.x);
    return 0;
}