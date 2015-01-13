#include <algorithm>
#include <iostream>
#include <set>

int main()
{
    std::set<int> s{ 3, 1, -14, 1, 5, 9 }; 
    std::set<int>::iterator result;
 
    int max_value = 6;
    result = std::max_element(std::begin(s), std::find_if(std::begin(s), std::end(s), [&](int i) { return i >= max_value; } ) );
    std::cout << "max element is: " << *result;
}