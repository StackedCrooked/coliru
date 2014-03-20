#include <iostream>
#include <vector>
#include <initializer_list>
 

 
int main()
{
    auto al = {10, 11, 12};   // special rule for auto
 
    std::cout << "The list bound to auto has size() = " << al.size() << '\n';
 
    std::cout << "Test for last element = " << *(al.end()-1) << '\n';
}