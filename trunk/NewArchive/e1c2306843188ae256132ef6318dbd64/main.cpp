#include <iostream>
#include <thread>

int tomstringlength(char const* str) {
    int counter = 0;
    while(*str != 0) {
        ++str;
        ++counter;
    }
    return counter;
}


int main() {
    std::cout << tomstringlength("tombo");    
}