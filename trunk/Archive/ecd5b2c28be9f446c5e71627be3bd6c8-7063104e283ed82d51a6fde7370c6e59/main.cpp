#include <iostream>

int counter;

void loop(int n) {
    ++counter;
    ++n;
    for(int i = n; i < 10; i++) loop(i);
}

int main() {
    counter = 1;
    for(int i = 0; i < 10; i++) loop(i);
    
    std::cout << counter << std::endl;
}