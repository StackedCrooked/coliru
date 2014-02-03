#include <iostream>

int main() {
    int number = 0;

    if (std::cin.peek() == '\n') {
        number = 20;
    } else if (!(std::cin >> number)) {
        std::cout << "Invalid input.\n";
        //error handling
    }

    std::cout << "Number: " << number << '\n';    
}
