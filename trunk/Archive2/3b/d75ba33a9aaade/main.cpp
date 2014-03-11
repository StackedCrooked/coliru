#include <array>
#include <iostream>

struct v {
    int& operator[](std::size_t i) {
        return a[i];
    }
private:
    std::array<int, 3> a;
};

int main() {
    v x;
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;
    x[2] = x[0] + x[1];
    std::cout << x[2] << '\n';
    x[2] = x[0] - x[1];
    std::cout << x[2] << '\n';
}
