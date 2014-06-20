#include <iostream>

template<typename Function>
void invoke(Function f) {
    f();
}

int main() {
    invoke([] { std::cout << "Hello\n"; });
    invoke([] { std::cout << "There.\n"; });
}