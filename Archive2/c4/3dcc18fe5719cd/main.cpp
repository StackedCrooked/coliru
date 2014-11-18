#include <iostream>
template<class FT>
auto call_it(FT f) {
    return f();
}

int main() {
    std::cout << call_it([](){return 100;}) << "\n";
    call_it([](){std::cout << "Hello worlz\n";});
}