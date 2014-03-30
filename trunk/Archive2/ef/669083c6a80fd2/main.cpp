#include <iostream>
#include <typeinfo>
#include <vector>

void printType( const std::type_info& ti ) {
    std::cout << ti.name() << '\n';
}

// because cast to void is a non generic way to hide unused variable warning.
template <typename T> void ignore(T&&) {}

template<typename... Ts>
void expandVariadic(Ts&&... ts) {
    auto il { ( printType( typeid(std::forward<Ts>(ts)) ), 0)... };
    ignore(il);
}

int main(int argc, const char* argv[]) {
    expandVariadic(10, "hi", std::cout, std::vector<int>());
    return 0;
}