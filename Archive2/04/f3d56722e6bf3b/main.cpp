
#include <iostream>

int main () {
    int i = 7;
    int& ir = i;
    ir = (ir + 3) & ~(decltype(ir))3;
    std::cout << ir;
}