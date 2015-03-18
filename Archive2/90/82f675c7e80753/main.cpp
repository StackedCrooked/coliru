#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class Foo {
  public:
    Foo(initializer_list<int> i) {
      for (auto j : i) cout << j << ' ';
    }
};  


int main() {
  Foo foo({1, 2, 3});
}
