#include <cstddef>

template<size_t, typename, typename> class lol;

template<size_t n, typename T, typename U>
void f(const lol<n, T, U>& a) {
    a.print();
}

#include <iostream>

template<typename T>
struct special_function {
    template<typename U>
    void operator()(const U&) const {
        std::cout << T{1} << '\n';
    }
};

template<>
struct special_function<float> {
    template<typename U>
    void operator()(const U&) const {
        std::cout << 12.01212 << '\n';
    }
};

template<size_t n, typename T, typename U> 
struct lol {
    void print() const {
        std::cout << n;
    }
    
    template<typename F, size_t N, typename V, typename G>
    friend void special(const lol<N, V, G>& a) {
        special_function<F>()(a);
    }
};

int main() {
    lol<10, int, float> a;
    f(a);
    special<int>(a);
    special<float>(a);
}    
