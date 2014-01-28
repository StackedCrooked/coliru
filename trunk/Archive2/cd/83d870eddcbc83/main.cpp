#include <vector>
#include <string>
#include <iostream>
#include <iterator>
 
int main() 
{
    // c++11 initializer list syntax:
    std::vector<int> test (6, 123);
    std::copy(test.begin(), test.end(), std::ostream_iterator<int>(std::cout, " "));
 
}