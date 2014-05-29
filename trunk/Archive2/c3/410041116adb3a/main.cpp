#include <iostream>
#include <string.h>
#include <vector>
#define SIZE 10

int inline f(int r,int q)
{
    return (r*10)%q;
}

int main()
{
    using namespace std;
    char a[10]="abcd";
    cout << hexToInt(a,strlen(a));
    return 0;
}
