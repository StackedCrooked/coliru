#include <iostream>

int main() {
  int i = 0, j = 0;
    [&i = j] {
        ++i;
    }();
    std::cout << i << ' ' << j << '\n';
}
