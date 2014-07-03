#include <cstddef>
#include <type_traits>
#include <iostream>

template <typename T>
void sort ( std::true_type, T&& data ) {
    std::cout << "All the heapsorts" << std::endl;
}

template <typename T>
void sort ( std::false_type, T&& data ) {
    std::cout << "All the quicksorts" << std::endl;
}


template <typename T, std::size_t N>
void foo ( T (&value)[N] ) {
    sort( std::integral_constant<bool, (N < 20)>(), value );
}


int main () {
    
    int c_arr0[19];
    foo(c_arr0);

    int c_arr1[20];
    foo(c_arr1);
    
    
}
