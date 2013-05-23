#include <iostream>
#include <array>

template<typename T, size_t dim>
struct getTypeAtDim { typedef T type; };

template<typename T, size_t N>
struct getTypeAtDim<T[N],1> { typedef T type; };

template<typename T, size_t dim, size_t N>
struct getTypeAtDim<T[N],dim> : getTypeAtDim< T, dim-1> {};


template<typename T, size_t N>
struct getTypeAtDim<std::array<T,N>,1> { typedef T type; };

template<typename T, size_t dim, size_t N>
struct getTypeAtDim<std::array<T,N>,dim> : getTypeAtDim< T, dim-1> {};

template<typename T, size_t dim>
using typeAtDim = typename getTypeAtDim<T, dim>::type;




template<typename T> 
typeAtDim<T,1>& indexed(T& arr, const int& first) {
    return arr[first];
}

template<typename T, typename... Args> 
typeAtDim<T,sizeof...(Args) + 1>& indexed(T& arr, const int& first, const Args& ...rest) {
    return indexed(arr[first],rest...);
}

int main() {
    std::array<int,2> a1 = {1,2};
    std::array<int,2> a2 = {3,4};
    std::array<std::array<int,2>,2> a = {a1,a2};
    std::array<std::array<std::array<int,2>,2>,2> c = {a,a};
    int b[2][2] = {{5,6},{7,8}};
    
    
    std::cout << indexed(a,1,1) << std::endl;
    indexed(a,1,1) = 5;
    std::cout << indexed(a,1,1) << std::endl;
    std::cout << indexed(b,1,1) << std::endl;
    std::cout << indexed(c,1,1,1) << std::endl;
    indexed(c,1,1) = a1;
    std::cout << indexed(c,1,1,1) << std::endl;
    
}

