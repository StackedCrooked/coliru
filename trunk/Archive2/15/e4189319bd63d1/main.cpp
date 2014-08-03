#include <iostream>
#include <array>

int main() {
    try {
        std::array<int,10000000> arr;
        std::cout << arr[40] << std::endl;
    }
    catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
