#include <iostream>
#include <string>

int main() {
    std::string text;
    std::cout << "Please type a message: ";
    std::getline(std::cin, text);
    std::cout << '\n' << "User's Text: " << "\n" << text << '\n';
}