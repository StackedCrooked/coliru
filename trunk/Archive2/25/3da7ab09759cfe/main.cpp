#include <functional>
#include <iostream>
#include <random>

using namespace std;

class X {
   mt19937 generator{std::random_device{}()};
   uniform_int_distribution<unsigned> distribution{1,7};
public:
   decltype(bind(std::ref(distribution), std::ref(generator))) dice{
      bind(std::ref(distribution), std::ref(generator))
   };
};

int main() {
    X x;
    cout << x.dice() << ' ' << x.dice() << '\n';
}
