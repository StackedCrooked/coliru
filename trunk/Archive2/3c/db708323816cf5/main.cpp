#include <cstdio>
using namespace std;

int & f(int idx, int &i)
{
printf("this is f %s\n", idx ? "right" : "left");
return ++i;
}

int bar(int idx, int z) 
{
    printf("bar%d = %d\n", idx, z);
	return z;
}

int main()
{
    int x=5;
    f(0,x)= bar(0, bar(1, f(1,x)) + 1 );
    printf("final = %d\n",x);
    return 0;
}
