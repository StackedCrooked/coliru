#include <iostream>
#include <string>

int main() {
    // please use 'sensical' variable names
    std::string todo;
    int choice;

    std::cout << "What would you like to do today?\n";
    std::cin >> todo;

    std::cout << "So you want to " << todo << std::endl;

    std::cout << "Yes [1] or No [2]?\n";
    std::cin >> choice;
    if (choice == 1) {
        std::cout << "Oh, that sounds awesome!\n";
    } else {
        std::cout << "Then, goodbye.\n";
    }

    return 0;
}