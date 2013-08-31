#include <iostream>
#include <vector>
#include <typeinfo>


int main(void) {
    std::vector<std::vector<bool>> matrix = std::vector<std::vector<bool>>(10, std::vector<bool>(5, false));;

    std::cout << typeid(matrix[0][0]).name() << std::endl ;

    for(auto a : matrix[0]) {
        std::cout << a << ", "  ;
    }
    std::cout << std::endl ;

    for(auto a : matrix[0]) {
        a = true;
    }

    for(auto a : matrix[0]) {
        std::cout << a << ", "  ;
    }
    std::cout << std::endl ;

    return 0;
}