#include <iostream>

template <size_t dimension, typename T, size_t c0>
size_t get_extent(const T (&arr)[c0], size_t result=-1) {return !dimension?c0:result;}
template <size_t dimension, typename T, size_t c0, size_t c1>
size_t get_extent(const T (&arr)[c0][c1], size_t result=-1) {return get_extent<dimension-1>(arr[0],!dimension?c0:result);}
template <size_t dimension, typename T, size_t c0, size_t c1, size_t c2>
size_t get_extent(const T (&arr)[c0][c1][c2], size_t result=-1) {return get_extent<dimension-1>(arr[0],!dimension?c0:result);}
template <size_t dimension, typename T, size_t c0, size_t c1, size_t c2,size_t c3>
size_t get_extent(const T (&arr)[c0][c1][c2][c3], size_t result=-1) {return get_extent<dimension-1>(arr[0],!dimension?c0:result);}
template <size_t dimension, typename T, size_t c0, size_t c1, size_t c2,size_t c3,size_t c4>
size_t get_extent(const T (&arr)[c0][c1][c2][c3][c4], size_t result=-1) {return get_extent<dimension-1>(arr[0],!dimension?c0:result);}



int main() {
    float my_3d_array[11][22][33][44] ;

    std::cout << get_extent<0>(my_3d_array) << "\n";
    std::cout << get_extent<1>(my_3d_array) << "\n";
    std::cout << get_extent<2>(my_3d_array) << "\n";
    std::cout << get_extent<3>(my_3d_array) << "\n";    
}