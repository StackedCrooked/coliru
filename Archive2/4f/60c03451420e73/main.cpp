#include <iostream>

int main(int argc, char** argv) {
    char buffer[4096];
    while (std::cin.read(buffer, sizeof(buffer)), std::cin.gcount() > 0) {
        std::cout << "wtf\n";
    }
}

