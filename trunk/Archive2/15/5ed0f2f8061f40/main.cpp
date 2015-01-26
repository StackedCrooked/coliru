#include <iostream>

auto LazyAdder(int x, int y) -> decltype(auto) {
    return [x, y]() {
        return x + y;
    };
}

auto SemiLazyAdder(int x) -> decltype(auto) {
    return [x](int y) {
        return x + y;
    };
}

template <typename Sheepy, typename... Args>
void functional_printer(Sheepy function, Args... args) {
    std::cout<<function(args...)<<std::endl;
}

int not_a_lambda(int x, int y) {
    return x + y;
}

template <typename Sheepy>
void Subroutine(Sheepy function) {
    functional_printer(function,3);
}

void Subroutine() {
    auto function = SemiLazyAdder(2);
    functional_printer(function, 3);
}

int main() {
    int two = 2;
    int three = 3;
    auto dumber_than_sheep = [two, three]() {
        return two + three;
    };
    
    auto not_worth_a_lambda = [](int x, int y) {
        return x + y;
    };
    
    auto baabaa = LazyAdder(2, 3);
    
    auto meeeeh = SemiLazyAdder(2);
    
    functional_printer(not_a_lambda, 2, 3);
    functional_printer(not_worth_a_lambda, 2, 3);
    functional_printer(dumber_than_sheep);
    functional_printer(baabaa);
    Subroutine(meeeeh);
    Subroutine();
}
