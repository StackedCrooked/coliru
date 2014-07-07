#include <stdio.h>
int main()
{
    float grain = 7007.f * 64.79891f;
    float pounds = 1.001f * 453592.37;
    printf("%f  %f  Equal? %s", grain, pounds, (grain == pounds) ? "Yes" : "No");
    return 0;
}