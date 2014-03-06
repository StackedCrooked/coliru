#include <iostream>
#include <string>

int * global;

const int * foo() {
    return global;
}

int main () {
    global = new int (5);
    
    auto&& gref = * foo();
    gref = 5;
    
    delete global;
}