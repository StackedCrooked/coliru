#include <iostream>

int M(int i)
{
    printf("%d\n",i++);	
}

int main ()
{
int i=10;
printf("%d\n",M(i));  
/*
I think calling M here should  print 10 and a garbage return value from the function call, as it is not returing anything.
but the output is 10 and 3 ? Can you explain this ? 
*/
return 0;
}