#include <algorithm>
#include <iostream>

template<class T, std::size_t N>
void f(T (&)[N]) { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main(int argc, char** argv) {
    int x[42][3];
    f(x);

    return 0;
}