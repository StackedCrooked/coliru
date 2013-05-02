#include <iostream>

struct some_inception {};

void do_stuff();
void sleep();

void go_on_a_plane() {
    throw some_inception();
    do_stuff();
}

void do_stuff() {
    std::cout << "blah\n";
    sleep();
}

void sleep() {
    try {
        std::cout << "I never sleep on planes. I don't wanna get incepted.\n";
    } catch (some_inception&) {
        std::cout << "I was incepted!\n";
    }
}

int main() {
    do_stuff();
    go_on_a_plane();
}
