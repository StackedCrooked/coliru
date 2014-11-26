#include <vector>
#include <iostream>

struct X {
    std::vector<int> vec;

    X() : vec(3, 123) { // initialize the vector to contain {123, 123, 123}
        vec[1] = 0;     // set the middle 123 to be 0 so: {123, 0, 123}
    }
    
    void invert() {     // invert values, so: {0, 123, 0}
        vec[0] = 0;     // notice how vec is accessible here
        vec[1] = 123;
        vec[2] = 0;
    }
};

int main() {
    X x;
    for (auto i : x.vec)
        std::cout << i << '\n';
        
    std::cout << "------------------\n";
    
    x.invert();
    for (auto i : x.vec)
        std::cout << i << '\n';
}