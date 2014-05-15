#include <stdio.h>
#include <string.h>

#include <iostream>

int main() {
    auto f = fopen("main.cpp", "r");
    
    auto show_file = [](FILE* f) {
        char d[sizeof(FILE)];
        memcpy(d, f, sizeof(FILE));
        for(auto c : d)
            std::cout << std::hex << int(c) << ' ';
        std::cout << '\n';
    };
    
    show_file(f);
    char x[10];
    fgets(x, 3, f);
    show_file(f);
}