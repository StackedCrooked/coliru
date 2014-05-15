#include <string.h>
#include <stdio.h>

#define MAX_NUMBER    100

int main(void)
{
    int odd_sum=0, odd_count = 0;
    int even_sum =0, even_count = 0;
    for (int i = 1; i < MAX_NUMBER; i++)
    {
        if (i%2)
        {
            odd_sum+=i;
            odd_count++;
        }
        else
        {
            even_sum+=i;
            even_count++;
        }
    }
    
    printf("There are %d even numbers, sum of the even numbers: %d\n", even_count, even_sum);
    printf("There are %d odd numbers, sum of the odd numbers: %d\n", odd_count, odd_sum);
}