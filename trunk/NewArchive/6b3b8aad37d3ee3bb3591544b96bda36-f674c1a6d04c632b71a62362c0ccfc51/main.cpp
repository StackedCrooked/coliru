#include <iostream>


template<typename T>
struct some_template {
    static void print() {
        std::cout << "original class template" << std::endl;
    }
};


template<>
struct some_template<int> {
    static void print() {
        std::cout << "class template specialization for int" << std::endl;
    }
};


template<typename T>
void some_func(T) {
    std::cout << "original function template" << std::endl;
}


template<>
void some_func(double) {
    std::cout << "function template specialization for double" << std::endl;
}


int main() {
    some_template<float>::print();
    some_template<int>::print();
    
    some_func(42);
    some_func(9.8);
}

