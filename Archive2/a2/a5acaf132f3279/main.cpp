#include <iostream>

namespace test_ns {
    int x = 100;
}

using namespace test_ns;

int main(){
    int y = x;
    std::cout << y;
    return 0;
}