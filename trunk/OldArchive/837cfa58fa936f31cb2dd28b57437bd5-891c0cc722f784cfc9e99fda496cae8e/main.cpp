#include <iostream>

class foo {
    void blah(size_t, int){}
    void(foo::*blahalias)(size_t, int) = &foo::blah;
};

int main() {}