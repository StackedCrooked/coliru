#include <iostream>

void foo(char (&blah)[4]);
void bar(char blah[4]);

int main()
{
     bar("Hahahaha"); // Works
     foo("Hahahaha"); //Doesn't work
}