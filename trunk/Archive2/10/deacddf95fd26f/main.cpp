#include <iostream>

template<class ...T>
void f(T... args) { int dummy[] { (std::cout << args << "\n", 0)..., 0 }; (void) dummy; }

int main(int argc, char** argv) {
    // works
    f<int>(3, 4);
    
    // fails
    auto x = f<int>; x(3, 4);
    
    return 0;
}