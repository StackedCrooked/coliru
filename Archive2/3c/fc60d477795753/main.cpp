#include <iostream>

namespace STD {
class STRING {};
}

int main() {
    STD::STRING* a = new STD::STRING();
    a->~STRING();
}