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
    int two = 2;
    int three = 3;
    auto dumber_than_sheep = [two, three]() {
        return two + three;
    };
    
    auto baabaa = SemiLazyAdder(two);
    
    auto meeeeh = LazyAdder(two,three);
    
    std::cout<<dumber_than_sheep()<<std::endl;
    std::cout<<baabaa(three)<<std::endl;
    std::cout<<meeeeh()<<std::endl;
}
