#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>

namespace Csc
{
/** Retrieves the number of array elements in the innermost dimension of an array */
template<typename T, std::size_t N>
std::size_t length_of(T const (&)[N])
{
  return N;
}

/** Retrieves the end iterator for a statically sized array */
template<typename T, std::size_t N>
T *end_of(T (&arr)[N])
{
  return arr + length_of(arr);
}
}

int main()
{
    int arr[] = {0, 1, 2, 3, 4, 0};
    int const *start = std::find_if(arr, Csc::end_of(arr), std::bind1st(std::not_equal_to<int>(), 0));
    
    if(start != Csc::end_of(arr))
    {
        std::cout << *start << '\n';
    }
    else
    {
        std::cout << "start not found\n";
        return -1;
    }
    
    std::reverse_iterator<int const *> end = 
        std::find_if(std::reverse_iterator<int const *>(Csc::end_of(arr)),
                     std::reverse_iterator<int const *>(arr),
                     std::bind1st(std::not_equal_to<int>(), 0));
    if(end != std::reverse_iterator<int const *>(arr))
    {
        std::cout << *end << '\n';
    }
    else
    {
        std::cout << "end not found\n";
        return -1;
    }
}
