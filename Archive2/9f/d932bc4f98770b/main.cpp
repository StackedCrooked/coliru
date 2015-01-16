#include <iostream>

template<size_t dimension>
struct get_extent : get_extent<dimension-1> {
    template<class T, size_t L>
    get_extent(T (&a)[L]) 
    : get_extent<dimension-1>(a[0])
    {}
};
template<>
struct get_extent<0> {
    template<class T, size_t L>
    get_extent(T (&a)[L]) 
    : value(L)
    {}
    
    operator size_t() const {return value;}
    
    size_t value;
};



int main() {
    float my_3d_array[11][22][33][44] ;

    std::cout << get_extent<0>(my_3d_array) << "\n";
    std::cout << get_extent<1>(my_3d_array) << "\n";
    std::cout << get_extent<2>(my_3d_array) << "\n";
    std::cout << get_extent<3>(my_3d_array) << "\n";    
}