#include <cstdio>

using std::printf;

int main()
{
    int i = 101;
    decltype(1, i) var = i;
    var = 20;
    printf("%d\n", i); // will print 20
    
    return 0;
}