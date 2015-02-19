#include <iostream>
#include <string>
#include <vector>

std::vector<int> f1() {
    return std::vector<int>();
}

const std::vector<int> f2() {
    return std::vector<int>();
}

int main()
{
    auto v1 = f1();
    auto v2 = f2();
    
    return 0;
}
