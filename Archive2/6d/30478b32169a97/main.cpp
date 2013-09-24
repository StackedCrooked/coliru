#include <cstdio>

void read1(int *arrayn,int size)
{
    printf("enter your array elements\n");
    while((size+1))
    {
    scanf("%d",arrayn);
    arrayn++;
    size--;
    }
}

void read2(int *arrayn,int size)
{
if(size+1)
{
    scanf("%d",arrayn);
    read2(++arrayn,--size);
}
else return;
}

int main(){}