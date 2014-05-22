#include <cmath>
#include <iostream>

// Given a function T f(T x) and its derivative T g(T x), uses Newton's method to
// approximate a value for x such that f(x) == 0.  See:
// http://en.wikipedia.org/wiki/Newton's_method
template <typename T, typename Function1, typename Function2>
constexpr T newtonMethod(Function1 f, Function2 g, T guess, T threshold)
{
    return std::abs(f(guess)) <= threshold ? (guess) :
        (newtonMethod(f, g, guess-f(guess)/g(guess), threshold));
}

constexpr double myFunction(double x) { return x*x*2 + x - 2; }
constexpr double myDerivative(double x) { return 2*x + 1; }
constexpr double root = newtonMethod(myFunction, myDerivative, 5.0, 0.001);

int main()
{   
    std::cout << "Newton's method found an approximate root at " << root << ".\n";
    std::cout << "(The actual value of myFunction(" << root << ") is " << myFunction(root) << ".)" << std::endl;
}
