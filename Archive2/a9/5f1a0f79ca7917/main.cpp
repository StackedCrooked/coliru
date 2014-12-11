#include <iostream>
#include <vector>
#include <stdexcept>

int copied = 0;
int MAX_COPIES = 1000;

struct A {
    A() {
        static int c = 0;
        x = c++;
    }
    
    A(const A& other) {
        x = other.x;
        if (copied++ > MAX_COPIES) throw std::runtime_error("copied too often");
    }
    
    A& operator=(const A& other) {
        x = other.x;
        if (copied++ > MAX_COPIES) throw std::runtime_error("copied too often");
        return *this;
    }
    
    int x;
};

int main() {
    std::vector<A> v(10);
    v.reserve(100);
    
    for (auto& e : v) std::cout << e.x << " ";
    std::cout << "\n";
    
    MAX_COPIES = 10;
    try { v.emplace(v.begin() + 5); } catch (...) {
        std::cout << "error\n";
    }
    
    for (auto& e : v) std::cout << e.x << " ";
    std::cout << "\n";
    
    return 0;
}