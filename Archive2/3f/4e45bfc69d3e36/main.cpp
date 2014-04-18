#include <list>
#include <iostream>
 
int main()
{
    std::list<int> numbers;
 
    numbers.push_back(42);
    numbers.push_back(314159); 
 
    for (int i : numbers) { // c++11 range-based for loop
        std::cout <<"The pouf is put "<< i << " times" << '\n';
    } 
 
    return 0;
}