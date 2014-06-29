#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main(void)
{

    std::vector<int> numbers; // our array to be filled
    std::copy_n(std::istream_iterator<int>(std::cin), 5, std::back_inserter(numbers));
    
    std::cout << "Numbers: ";
    std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<int>(std::cout));
    std::cout << std::endl; // New line
    
   
}