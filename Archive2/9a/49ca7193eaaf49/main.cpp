#include <cstdlib>
#include <iostream>
#include <set>


int main () {
    std::srand(1337);
    std::size_t num_values = 20;
    std::size_t num_max = 100;
    
    std::set<std::size_t> numbers;
    
    while (numbers.size() < num_values)
        numbers.insert(rand() % num_max);
 
    for (std::set<size_t>::iterator i = numbers.begin(); i != numbers.end(); ++i) 
        std::cout << *i << "\n";
}
