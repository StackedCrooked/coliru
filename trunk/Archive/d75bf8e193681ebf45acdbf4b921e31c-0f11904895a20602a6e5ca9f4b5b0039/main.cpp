#include <iostream>

bool i = false;

bool fuck() {
    bool done = true;
    return (done && (i = true));
}

int main() {
    bool x = fuck();
}