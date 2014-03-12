#include <iostream>
#include <string>

int main() {
    int input1 = 0;
    std::string in;
    while (true) {
        std::cout << "Please enter a positive value: ";
        std::getline(std::cin, in);
        if (in.find(' ') == std::string::npos) {
            input1 = std::stoi(in);
            // do what you want with input1
        }
    }
}