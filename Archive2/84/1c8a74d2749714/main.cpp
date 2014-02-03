#include <iostream>
#include <string>
#include <vector>

template<typename T>
struct tuple {
    template<std::size_t N>
    int get() const {
        return N;
    }
};

int main() {
    tuple<int> x;
    return x.get<0>();
}