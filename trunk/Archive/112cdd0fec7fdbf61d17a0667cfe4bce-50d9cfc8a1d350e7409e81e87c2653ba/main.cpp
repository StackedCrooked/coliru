#include <limits.h>
#include <stdlib.h>     /* malloc, free, rand */
#include <stdio.h>
#include <string>
#include <iostream>     // std::cout
#include <utility>      // std::pair
#include <functional>   // std::equal_to
#include <algorithm>    // std::mismat
#include <vector>

template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}

int main()
{
  std::cout<<std::vector<int>(5);
  return 0;
}