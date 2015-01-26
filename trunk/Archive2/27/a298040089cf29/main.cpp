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

template <typename Goaty, typename... Args>
void plain_old_function_printer(Goaty function, Args... args) {
    std::cout<<function(args...)<<std::endl;
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
    
    auto baabaa = LazyAdder(two,three);
    
    lambda_printer(dumber_than_sheep);
    plain_old_function_printer(not_worth_a_lambda, two, three);
    lambda_printer(baabaa);
}
