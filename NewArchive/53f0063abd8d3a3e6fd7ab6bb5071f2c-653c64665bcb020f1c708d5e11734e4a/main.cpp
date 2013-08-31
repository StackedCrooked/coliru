#include <iostream>
#include <stdexcept>

void five() {
    throw std::runtime_error("Error bubbling up the call stack - I don't need to rethrow it or anything!");
}
void four() {
    five();
}
void three() {
    four();
}
void two() {
    three();
}
void one() {
    two();
}

int main() {
    try {
        one();
    } catch(std::runtime_error e) {
        std::cout << "Looks like we got an exception from calling one() - which has no error handling in it at all! The exception bubbled up the call stack.\n";
        std::cout << e.what() << "\n";
    }
    return 0;
}