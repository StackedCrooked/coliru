#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
wstring get_dms_by_location(double location) // -30.91°   to   -30°54′36.00″
{
    wchar_t buf[64]={0};
    bool sign = location > 0.0;
    location = abs(location);
    int d = (int)location;
    location = (location - d) * 60;
    int m = (int)location;
    location = (location - m) * 60;
    if(sign)
        swprintf(buf, 63, L"+%d° %02d′ %05.2lf\"", d, m, location);
    else
        swprintf(buf, 63, L"-%d° %02d′ %05.2lf\"", d, m, location);
    return buf;
}
int main(void)
{
    char A[] = "Take the test.";
    char *B = malloc(strlen(A) + 1);
    strcpy(B, A);
    A[0] = 'M';
    printf("A = %s\nB = %s", A, B);
 
    return 0;
}