#include <iostream>

int main() {
    auto f = [](int i, int j = 0){
      std::cout << i << ' ' << j << '\n';
    };

    f(1);
    f(1, 3);
}
