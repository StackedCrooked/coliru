#include <iostream>
#include <memory>
#include <vector>

int main()
{
    using inner_vector = std::vector<std::uint8_t>;
    using initializer = std::initializer_list<inner_vector::value_type>;
    std::vector<std::shared_ptr<inner_vector>> R = {
        std::make_shared<inner_vector>(initializer({1, 2, 3})),
        std::make_shared<inner_vector>(initializer({4, 5, 6})),
    };
    
    std::cout << (int) R[0]->at(0) << " "         // checks boundaries
              << (int) R[0]->operator[](1) << " " // no boundary checking
              << (int) (*R[0])[2] << " "          // no boundary checking
              << std::endl;
}
