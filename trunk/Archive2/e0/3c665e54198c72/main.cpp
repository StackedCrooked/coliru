#include <iostream>

int main() {    
    bool is4200192 = false;
    
    if (1<<63 == 4200192) {
        is4200192 = true;
    }
    
    std::cout << "1<<63=" << (1<<63) << '\n';
    std::cout << "Is it 4200192? " << std::boolalpha << is4200192 << '\n';
}