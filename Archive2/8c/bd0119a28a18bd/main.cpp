#include <type_traits>
#include <iostream>

template<class T>
void func(T&& param) {
    if (std::is_same<typename std::decay<T>::type,int>::value) 
        std::cout << "param is an int\n";
    else 
        std::cout << "param is not an int\n";
}

int main() {
    int three = 3;
    func(three);
}