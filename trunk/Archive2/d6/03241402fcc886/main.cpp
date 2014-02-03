#include <iostream>

int main() {
    int m[][4] = {
                    { 0, 1, 2, 3 },
                    { 4, 5, 6, 7 },
                    { 8, 9, 0, 1 },
                    { 2, 3, 4, 5 },
                 };

    for(auto &line : m) {
        for(auto &value : line) {
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    }
}