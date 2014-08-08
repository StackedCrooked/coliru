#include <iostream>
#include <vector>

void foo(std::vector<bool>& p)
{
    for( auto&& b : p )
        b=true;
}

int main() {
    std::vector<bool> p = { true, false, true, true };
    foo(p);
    for(const auto& b : p) {
        std::cout << b << '\n';
    }
}