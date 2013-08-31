#include <iostream>

class A {
public:
    char stuff[100];
    size_t len;
    A(): stuff{0}, len{0} {}
};

#include <vector>

int main() {
    std::vector<A> as(10);
    for(auto&& i : as) {
        std::cout << "Length: " << i.len << '\n';
    }
}