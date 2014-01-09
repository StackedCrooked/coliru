#include <functional>
#include <iostream>
#include <random>

using namespace std;

class X {
   mt19937 generator = mt19937{std::random_device{}()};
   uniform_int_distribution<unsigned> distribution = uniform_int_distribution<unsigned>(1,7);
public:
   decltype(bind(distribution, generator)) dice = bind(distribution, generator);
};

int main() {
    X x;
    cout << x.dice() << ' ' << x.dice() << '\n';
}
