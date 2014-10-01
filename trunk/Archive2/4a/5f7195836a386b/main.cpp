#include <iostream>
#include <vector>

// A function that expects a ref. to const callable
template<typename Callable>
double some_function(const Callable& c) {
    double result = 0.0;
    std::vector<double> x(2);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j)
        {
            x[0] = i;
            x[1] = j;
            c(x, result);
        }
    }
    return result;
}

// The function mutator allowing non-const functors to be used in a const context
template<typename Callable>
struct FunctionMutator {
    FunctionMutator(Callable& callable) : c(&callable) {}
    bool operator()(const std::vector<double>& x, double &f) const {
        return (*c)(x, f);
    }
    mutable Callable* c;
};

// A helper function to make FunctionMutators without having to specify the
// template parameters
template<typename Callable>
FunctionMutator<Callable> make_mutable(Callable& c) {
    return FunctionMutator<Callable>(c);
}

// Some user-provided function with mutating state
struct MyFunctor {
    double internal_data;
    bool operator()(const std::vector<double>& x, double& f) {
        internal_data += x[0];
        f = internal_data * x[1];
        return true;
    }
};

// Example usage...
int main()
{
    MyFunctor func;
    std::cout << some_function(make_mutable(func)) << "\n";
    return 0;
}