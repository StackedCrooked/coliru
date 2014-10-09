#include <iostream>
#include <string>
#include <vector>

#include <algorithm>
#include <cstdlib>
#include <iterator>

#define PRINT_CONTAINER(container) std::cout << #container << " : "; \
    std::copy(std::begin(container), std::end(container), std::ostream_iterator<decltype(*std::begin(container))>(std::cout, " ")); \
    std::cout << std::endl

struct Numbers
{
    int numbers[5];
};

int main()
{    
    Numbers num1;
    std::generate(std::begin(num1.numbers), std::end(num1.numbers), std::rand);
    
    Numbers num2 = num1;

    PRINT_CONTAINER(num1.numbers);
    PRINT_CONTAINER(num2.numbers);
    
}
