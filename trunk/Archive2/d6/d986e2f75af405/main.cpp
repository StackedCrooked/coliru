#include <vector>
#include <iostream>
 
int main()
{
    std::vector<const char *> numbers;
 
    const char* a = "65656";
 
    numbers.push_back("42");
    numbers.push_back("314159"); 
    numbers.push_back(a);
 
    for (const char* i : numbers) { // c++11 range-based for loop
        std::cout << i << '\n';
    } 
    std::cout << a << '\n';
    return 0;
}