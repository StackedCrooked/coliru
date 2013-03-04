#include <vector>
#include <iostream>

int main() {
    std::vector<int> v;
    int stuff[] = {0,1,2,3};
    v.assign(stuff,stuff + 4);
    for(auto& i : v)
        std::cout << i << ' ';
}