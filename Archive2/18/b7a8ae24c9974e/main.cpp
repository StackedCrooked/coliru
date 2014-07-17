#include <vector>
#include <iostream>


int main(void) {
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    for(auto& i : v) {
        [&i] {
            std::cout << i << std::endl;
        }();
        
        auto lambda = [&i] {
            std::cout << i << std::endl;
        };
        
        lambda();
        
        auto x = i;
        [&x] {
            std::cout << x << std::endl;
        }();
    }
}