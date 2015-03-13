#include <iostream>


int f() { return 42; }

template <int h()>
int g() { return h(); }

int main(int argc, char** argv) {
    std::cout << g<f>() << "\n";
    return 0;
}