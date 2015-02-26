#include <iostream>
#include <iomanip>

template<typename std::size_t n>
void printTable(int table[][n], size_t r) {
    for(std::size_t i = 0; i < r; ++i) {
        for(std::size_t j = 0; j < n; ++j) {
            std::cout << std::setw(5) << table[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "-----------------------------" << std::endl;
}

int main()
{
    constexpr std::size_t R = 5;
    constexpr std::size_t C = 5;
    
    int table[R][C] { };
    
    printTable(table, R);
    
    *(*(table + 0) + 0) = 100;
    *(*(table + 1) + 1) = 200;
    *(*(table + R - 1) + C -1) = 256;
    
    printTable(table, R);
}