#include <cstddef>
#include <iostream>

template <typename T, std::size_t N>
void fun ( T arr[N] ) {
    std::cout << "N: " << N << std::endl;
}

int main () {
    char x[13];
    fun( x );
}

