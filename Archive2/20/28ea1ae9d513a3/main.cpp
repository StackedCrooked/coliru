#include <iostream>
#include <vector>

int main() {
    std::vector<bool> v{0,1,0,1,0,1};
    for(auto& x : v)
        std::cout << x << ' ';
    std::cout <<'\n';
}