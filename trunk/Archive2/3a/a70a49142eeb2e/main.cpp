#include <iterator>
#include <iostream>

int sum(int* a, unsigned size, int acc = 0)
{
   if ( size == 0 )
      return acc ;
   else
      return sum(a+1, size-1, acc + *a);
}

int main()
{
   int array[] = { 1, 2, 3, 4, 5, 6 } ;
   unsigned array_size = std::end(array) - std::begin(array) ;

   std::cout << sum(array, array_size) << " is the sum of elements in array.\n" ;
}