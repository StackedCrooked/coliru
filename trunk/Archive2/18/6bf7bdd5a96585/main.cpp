#include <algorithm>
#include <iostream>

int main(int argc, char** argv) {
    int x[42][3];
    int y[42][3];
    
    using std::swap;
    std::cout << noexcept(swap(x, y)) << "\n";

    return 0;
}