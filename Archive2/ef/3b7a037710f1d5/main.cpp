#include <iostream>
#include <stdio.h>
using namespace std;

template <size_t N> int add(int (array)[N]) 
{
   int sum = 0;
   for (int i = 0; i < sizeof(array)/sizeof(array[0]); i += 1)
   {
       sum += array[i];
   }
   return sum;
}

int main()
{
    int array[4] = {1, 2, 3, 4};
    cout << add(array);
    
    return 0;
}