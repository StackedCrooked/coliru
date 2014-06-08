#include <iostream>
#include <algorithm>

template<typename T>
using identity = T;

template <typename It>
bool process(It first, It last)
{
  return std::all_of(first, last, 
                       [](  const identity<decltype(*first)>& i )
                       {
                            return i % 2 == 0; 
                       } 
                     ) ;
}

template bool process(int*, int*);

int main()
{
}