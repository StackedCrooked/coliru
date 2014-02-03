#include <iostream>
#include <string>
#include <vector>

struct tuple {
    template<std::size_t N>
    int get() const {
        return N;
    }
};

int main() {
    tuple x;
    x.get<1>();
}