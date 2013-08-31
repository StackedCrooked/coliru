#include <tuple>
#include <iostream>

struct divmod_expr {
    std::tuple<int, int> operator%(int divisor) {
        return std::make_tuple(dividend / divisor, dividend % divisor);
    }
    int dividend;
};

struct divmod_t {} divmod;

divmod_expr operator%(int dividend, divmod_t) {
    return { dividend };
}

int main() {
    int a;
    std::tie(a, std::ignore) = 15 %divmod% 2;
    std::cout << a;
}
