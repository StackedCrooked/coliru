#include <iomanip>
#include <iostream>

int main() {
    char memory[] = "lelwot";
    std::cout << std::hex << static_cast<int>(memory[5]);
}