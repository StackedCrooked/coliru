#include <vector>
#include <boost/container/vector.hpp>
#include <stdexcept>
#include <iostream>

class A {};
class B {
public:
    int x;
    B(A) { throw std::runtime_error("Welp."); }
    B() : x(0) {}
    B(const B&) : x(1) {}
    B(B&&) : x(2) {}
};

int main() {
    boost::container::vector<B> b;
    b.push_back(B());
    auto it = b.begin();
    try {
        b.emplace_back(A());
        it = b.begin();
    } catch(...) {
    }
    std::cout << it->x;
}
