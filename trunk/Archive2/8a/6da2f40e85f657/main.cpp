#include <iostream>

template<class ...T>
void f(T... args) { int dummy[] { (std::cout << args << "\n", 0)..., 0 }; (void) dummy; }

int main(int argc, char** argv) {
    f<int>(3, 4);
    return 0;
}