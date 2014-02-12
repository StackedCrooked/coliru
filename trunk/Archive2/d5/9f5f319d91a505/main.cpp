#include <iostream>

template<class T>
struct A {
    T data_;

    explicit A(const T& data): data_{data} {}
    
    T& operator [] (size_t i) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        
        return data_;
    }
    
    const T operator [] (size_t i) const {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        
        return data_;
    }
};

int main() {
    A<double> a{3.5};
    
    std::cout << a[100500] << std::endl;
}