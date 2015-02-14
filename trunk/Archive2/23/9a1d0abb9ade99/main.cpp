#include <iostream>

struct Tracked {
    Tracked() { std::cout << "default-ctor\n"; }
    Tracked(const Tracked &) { std::cout << "copy-ctor\n"; }
    Tracked(Tracked &&) { std::cout << "move-ctor\n"; }
    ~Tracked() { std::cout << "dtor\n"; }
};

void do_it(Tracked &&t) {
    //
}

int main() {
    Tracked t;
    do_it(Tracked{t});
}