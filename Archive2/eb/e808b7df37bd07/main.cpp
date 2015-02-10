#include <iostream>

void func(int* usedNum, int wher)
{
    *usedNum = *usedNum + 1 > wher ? ++(*usedNum) : wher + 1; 
}

int main()
{
   int a(1), b(2); 
   func(&a, b); 
}
