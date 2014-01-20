#include <iostream>
#include <iomanip>

int main() {
    bool t = 1;
    bool f = 0;
    std::cout << std::boolalpha << t << ' ' << f << std::noboolalpha << '\n';
    int x = true;
    int y = false;
    std::cout << x << ' ' << y;
}