template <typename T>
struct perform_indirection_t {
    typedef T& result;
    static result call(T& t) { return t; }
};

template <typename T>
struct perform_indirection_t<T*> {
    typedef typename perform_indirection_t<T>::result result;
    static result call(T* t) { return perform_indirection_t<T>::call(*t); }
};

template <typename T>
typename perform_indirection_t<T>::result perform_indirection(T t) {
    return perform_indirection_t<T>::call(t);
}

#include <iostream>

int main() {
    int x = 0;
    int* p = &x;
    int** pp = &p;
    int*** ppp = &pp;
    int**** pppp = &ppp;
    int***** ppppp = &pppp;
    
    perform_indirection(ppppp) = 1;
    std::cout << x;
}