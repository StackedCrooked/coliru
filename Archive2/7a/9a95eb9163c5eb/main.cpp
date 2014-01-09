#include <functional>
#include <iostream>
#include <random>

using namespace std;

class X {
   mt19937 generator{std::random_device{}()};
   uniform_int_distribution<unsigned> distribution{1,7};
public:
   decltype(bind(distribution, generator)) dice{bind(distribution, generator)};
};

int main() {
    X x;
    cout << x.dice() << ' ' << x.dice() << '\n';
}
