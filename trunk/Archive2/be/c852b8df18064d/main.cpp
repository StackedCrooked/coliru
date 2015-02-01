#include <stdio.h>

void bar()
{
    printf("HI\n");
}

void foo()
{
	int val;
  	int another = val;
  	if (val != another)
    {
     	bar(); 
    }
}

int main() {
    bar();
	foo();
	return 0;
}