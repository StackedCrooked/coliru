#include <iostream>

int main() {
    for(unsigned i = 1; i <= 100; ++i) {
        bool by_three = i % 3 == 0;
        bool by_seven = i % 7 == 0;
        if(by_three && by_seven) {
            std::cout << "Unviginti\n";
        }
        else if(by_three) {
            std::cout << "Tri\n";
        }
        else if(by_seven) {
            std::cout << "Sept\n";
        }
    }
}