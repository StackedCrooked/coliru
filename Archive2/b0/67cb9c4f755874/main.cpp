#include <iostream>

enum lol {
    one, two 
};

struct what {
    lol x;
    explicit what(lol y): x(y) {}
};

int main() {
    what x(2);
}