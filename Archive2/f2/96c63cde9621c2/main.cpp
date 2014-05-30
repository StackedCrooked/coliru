template<class First, class Second>
bool all_equal(const First& first, const Second& second) 
{return first==second;}

template<class First, class Second, class...Rest>
bool all_equal(const First& first, const Second& second, const Rest&...rest) 
{return first==second && all_equal(second, rest...);}

#include <iostream>
int main() {
    std::cout << all_equal(4, 4, 4);    
}