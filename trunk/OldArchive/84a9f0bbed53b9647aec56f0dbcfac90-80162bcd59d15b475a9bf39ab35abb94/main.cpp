#include <iostream>

class c1 {
public:
    const int x; // constant data
    c1() : x(0) {}; // constructor initializes x to 0
    void xplus2() { // this function can modify x
        *const_cast<int*>(&x) += 2; // add 2 to x
    }
};

int main() {
    c1 *cc = new c1();
    cc->xplus2();
    
    std::cout << cc->x << std::endl;
    return 0;
}