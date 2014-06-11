#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    try {
        throw std::runtime_error("wtf");
    }
    catch (std::exception& ಠ_ಠ) {
        std::cout << ಠ_ಠ.what() << std::endl;
    }
}