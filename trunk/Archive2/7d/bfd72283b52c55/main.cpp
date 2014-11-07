#include <iostream>
#include <type_traits>


using namespace std;

int main()
{
   auto k = { 1, 2 };
   static_assert(std::is_same<std::initializer_list<int>, decltype(k)>::value, "Error!"); 
}