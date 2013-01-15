#include <vector>
#include <iostream>

template<size_t n, size_t m>
struct pseudo {
    template<typename T>
    struct pseudorange {
        T& t;
        pseudorange(T& p): t(p) {}

        decltype(std::begin(T())) begin() {
            return std::begin(t)+n;
        }
        decltype(std::begin(T())) end(){
            return std::begin(t)+m;
        }
    };

    template<typename T>
    friend pseudorange<T> operator| (T& container, pseudo) {
        return pseudorange<T>(container);
    }
};

template<size_t n, size_t m, typename T>
auto range(T& container) -> decltype(container | pseudo<n,m>()) {
    return container | pseudo<n,m>();
}

int main() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    for(auto& i : range<0,5>(v)) {
        std::cout << i << '\n';
    }
}
