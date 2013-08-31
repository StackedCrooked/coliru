#include <cstddef>

template<size_t, typename, typename> class lol;

template<size_t n, typename T, typename U>
void f(const lol<n, T, U>& a) {
    a.print();
}

#include <iostream>

template<size_t n, typename T, typename U> 
struct lol {
    void print() const {
        std::cout << n;
    }
    
    template<typename F, size_t N, typename V, typename G>
    friend void special(const lol<N, V, G>&) {
        std::cout << F{1} << '\n';
    }
    
    template<size_t N, typename V, typename G>
    friend void special<float>(const lol<N, V, G>&) {
        std::cout << 12.01213 << '\n';
    }
};

int main() {
    lol<10, int, float> a;
    f(a);
    special<int>(a);
    special<float>(a);
}    
