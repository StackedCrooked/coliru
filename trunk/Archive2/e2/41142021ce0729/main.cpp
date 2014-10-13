#include <iostream>
#include <typeinfo>

template <typename T>
class Data {
public:
    Data() {
        std::cout << "creating Data<" << typeid(T).name() << '>' << std::endl;
    }
    ~Data() {
        std::cout << "destroying Data<" << typeid(T).name() << '>' << std::endl;
    }
    int x = 0;
};

template<typename T>
class A {
    static Data<T> data;
public:
    A() {
        // this is necessary for data to be instantiated
        std::cout << data.x << std::endl;
    }
 };

// This also should be in a header
template<typename T>
Data<T> A<T>::data;

int main(){
    A<int> aInt;
    A<float> aFloat;
}