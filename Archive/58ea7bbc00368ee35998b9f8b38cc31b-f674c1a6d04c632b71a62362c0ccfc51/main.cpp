#include <list>
#include <iostream>

int main() {
    std::list<int> numbers;
    numbers.push_back(3);
    numbers.push_back(2);
    numbers.push_back(4);
    numbers.push_back(5);

    std::list<int> temporary;
    auto move_from = std::next(numbers.begin(), 2);
    temporary.splice(temporary.begin(), numbers, move_from, std::next(move_from));
    auto move_to = std::next(numbers.begin(), 1);
    numbers.splice(move_to, temporary);
    
    for(int& v : numbers) 
        std::cout << v << ' ';
}