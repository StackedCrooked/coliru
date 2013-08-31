#include <iostream>

template<class> struct void_{ typedef void type; };

template<class T, class = void> struct is_iterator;
template<class T> struct is_iterator<T, typename void_<typename T::iterator_category>::type>{ typedef void type; };
template<class T> struct is_iterator<T*, void>{ typedef void type; };
template<class T> struct is_iterator<T const*, void>{ typedef void type; };

void insert(unsigned long long, int){
    std::cout << "scalar overload\n";
}

template<class T>
void insert(T, T, typename is_iterator<T>::type* = 0){
    std::cout << "iterator overload\n";
}

int main(){
    insert(1, 2);
    int* a = 0;
    insert(a, a);
}