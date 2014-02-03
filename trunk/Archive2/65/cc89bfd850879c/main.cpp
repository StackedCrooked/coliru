#include <stdio.h>

int main()
{
int person, i;
int pancake[50];

printf("Enter Number Of People: ");
scanf("%d", &person);

for (i=0; i<person; i++)
{
    printf("Person [%d]: ", i);
    scanf("%d",&pancake[i]);
}

for (i=0; i<person; i++)
  {
    if (pancake[0]<pancake[i])
    {
        pancake[0] = pancake[i];
    }
  }
  printf("Most pancakes eaten is %d\n", pancake[0]);
}