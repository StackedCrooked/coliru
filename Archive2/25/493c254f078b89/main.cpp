
template<typename T>
struct storage {
    const T* ptr;
    storage(const T& x): ptr(&x) {}
};

template<typename T>
storage<T> make_storage(const T& t) {
    return { t };
}

#include <iostream>


struct test {
    test() = default;
    test(const test&) = default;
    
    ~test() {
        std::cout << "~test()" << std::endl;
    }
};


int main() {
    test t;
    t.~test();
    
    int i = 1;
    i = i << 64;
}