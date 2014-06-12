#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
int main()
{
    std::set<std::string> v1;
    std::set<std::string> v2;
    
    v1.insert("hi");
    v2.insert("hello, there!");
    v2.insert("hi");
 
    std::vector<std::string> v_symDifference;
 
    std::set_symmetric_difference(
        v1.begin(), v1.end(),
        v2.begin(), v2.end(),
        std::back_inserter(v_symDifference));
 
    for(std::string n : v_symDifference)
        std::cout << n << ' ';
}