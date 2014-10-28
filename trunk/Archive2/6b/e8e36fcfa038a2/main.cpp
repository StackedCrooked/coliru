#include <iostream>

template<class ...T>
void f(T... args) { int dummy[] { ((std::cout << args << "\n")?1:0, 0)..., 0 }; (void) dummy; }

int main(int argc, char** argv) {
    // works?!
    f<int, int>(3, 4, nullptr);
    
    // fails
    auto x = f<int, int>; x(3, 4, "bye");
    
    return 0;
}