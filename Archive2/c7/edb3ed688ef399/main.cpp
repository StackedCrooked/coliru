#include <type_traits>
#include <iostream>
#include <vector>

template<typename Iterator>
typename std::iterator_traits<Iterator>::value_type fn(
   Iterator,
   Iterator,
   typename std::iterator_traits<Iterator>::value_type init
)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return init;
}

int main()
{
    std::vector<long> v;
    fn(v.begin(), v.end(), 0);
}