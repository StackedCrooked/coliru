#include <stdexcept>
#include <exception>
#include <iostream>

int main() {
    try {
        int i = 1;
        --i;
        throw std::logic_error("Exception one..");
    }
    catch(const std::logic_error& e) {
        std::cout << e.what() << '\n';
        try {
            int k = 1;
            --k;
            throw std::logic_error("What is wrong with you..");
        }
        catch(const std::logic_error& k) {
            std::cout << k.what();
        }
    }
}