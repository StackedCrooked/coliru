#include <iostream>


template<typename T>
struct some_template {
    static void print() {
        std::cout << "original template" << std::endl;
    }
};


template<>
struct some_template<int> {
    static void print() {
        std::cout << "specialization for int" << std::endl;
    }
};


int main() {
    some_template<float>::print();
    some_template<int>::print();
}

