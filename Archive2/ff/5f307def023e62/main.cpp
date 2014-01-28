#include <tuple>
#include <iostream>
using namespace std;

class F
{
    int val;
public:
    F() { }
    F(int _val) : val(_val) { }
    F(const F& other)
        : val(other.value()) {
        std::cout << "Copy constructor.\n";
    }
    int value() const {
        return val;
    }
};

int main() {
  F f{2};
  std::tie(f) = std::make_tuple(F{3});
  std::cout << f.value();
  return 0;
}