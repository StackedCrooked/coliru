#include <string>
#include <iterator>
#include <iostream>

template <typename iter_type>
std::reverse_iterator<iter_type> make_reverse(iter_type iter)
{
    return std::reverse_iterator<iter_type>(iter);
}

int main()
{
    std::string a("abc");
    auto it = make_reverse(a.end());
    
    while ( it != a.rbegin() )
        std::cout << *it++ ;
}