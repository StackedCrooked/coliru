#include <iostream>
#include <functional>

struct Solver {
    template <typename Callable, typename... Args>
    auto funcEvaluation(Callable&& c, Args&&... args) {
        return std::forward<Callable>(c)(std::forward<Args>(args)...);
    }
};

struct NonLinear {
    double nonLinearFunc(double x, double y, int m) {
        return (x + y) * m;
    }
};

int main() {
    Solver s;
    NonLinear nl;

    auto c = std::mem_fn(&NonLinear::nonLinearFunc); // Use call wrapper for member functions.
    std::cout << s.funcEvaluation(c, nl, 1.0, 2.0, 2) << std::endl;
}