#include <list>
#include <iostream>

int main() {
    std::list<int> numbers;
    numbers.push_back(3);
    numbers.push_back(2);
    numbers.push_back(4);
    numbers.push_back(5);
    
    std::list<int>::iterator first = std::next(numbers.begin(), 2);
    std::list<int>::iterator second = std::next(numbers.begin(), 1);
    std::iter_swap(first, second);
    
    for(int& v : numbers) 
        std::cout << v << ' ';
}