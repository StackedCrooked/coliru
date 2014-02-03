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

template<typename T>
int test(tuple<T>& x) {
    return x.template get<1>();
}

int main() {
    tuple<int> x;
    test(x);
}