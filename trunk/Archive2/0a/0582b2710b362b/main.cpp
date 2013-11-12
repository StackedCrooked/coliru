#include <type_traits>
#include <iterator>

template <class C>
using Value_Type = decltype(*std::begin(std::declval<C>()));

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    
    Value_Type<decltype(arr)> value = 42;
}
