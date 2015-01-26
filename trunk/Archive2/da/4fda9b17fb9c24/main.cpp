#include <iostream>

auto SemiLazyAdder(int x) -> decltype(auto) {
    return [x](int y) {
        return x + y;
    };
}

auto LazyAdder(int x, int y) -> decltype(auto) {
    return [x, y]() {
        return x + y;
    };
}

int main() {
    auto baabaa = SemiLazyAdder(2);
    std::cout<<baabaa(3)<<std::endl;
    
    auto meeeeh = LazyAdder(2,3);
    std::cout<<meeeeh()<<std::endl;
}
