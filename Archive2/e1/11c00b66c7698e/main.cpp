#include <cstdio>

void opaque(int*,int*);

int main()
{
    int array[100];
    for(int i=0; i<100; ++i){
       array[i] = 0;
    }
    opaque(array, array+100);
}
