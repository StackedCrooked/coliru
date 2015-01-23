#include <vector>
#include <iostream>
 
int main()
{
    std::vector<int> numbers;
    numbers.reserve(7);
 
    std::cout << "Size: " << numbers.size() << '\n';
 
    numbers[6] = 5;
 std::cout << "Size: " << numbers.size() << '\n';
    std::cout << numbers[6];
 
}