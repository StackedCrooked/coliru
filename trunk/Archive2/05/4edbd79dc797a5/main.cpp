#include <iostream>

struct st
{
    short a;
    int *b;
    char ch;
};

struct st2 {
    int *b;
    short a;
    char ch;
};

int main() {
    std::cout << sizeof(st) << ' ' << sizeof(st2) << '\n';   
}