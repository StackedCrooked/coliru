#include <iostream>

auto LazyAdder(int x, int y) -> decltype(auto) {
    return [x, y]() {
        return x + y;
    };
}

template <typename Sheepy>
void lambda_printer(Sheepy function) {
    std::cout<<function()<<std::endl;
}

int main() {
    int two = 2;
    int three = 3;
    auto dumber_than_sheep = [two, three]() {
        return two + three;
    };
    
    auto baabaa = LazyAdder(two,three);
    
    lambda_printer(dumber_than_sheep);
    lambda_printer(baabaa);
}
