#include <vector>
#include <iostream>
 
int main()
{
    std::vector<std::string> numbers;
    
    numbers.push_back("one");
    numbers.push_back("two");
    numbers.push_back("three");
    
    std::cout << "Second element: " << numbers[1] << '\n';
 
    numbers[0] = "five";
 
    std::cout << "Some Element: " << numbers[5] << std::endl;
    std::cout << '\n';
}