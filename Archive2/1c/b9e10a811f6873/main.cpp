#include <iostream>
#include <string>
#include <cstdio>

class named {
    int x;
    named(named&&) {
        this->x = 0;
    }
};

int main() {}