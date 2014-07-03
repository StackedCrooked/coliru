#include <cstddef>

namespace utility {
    template <typename T>
    struct size_getter {
        template <typename U>
        static std::size_t size( U&& value ) {
            return value.size();
        }
    };
    
    template <typename T, std::size_t N>
    struct size_getter<T[N]> {
        static std::size_t size ( T (&value)[N] ) {
            return N;
        }
    };
    
}

#include <type_traits>
#include <iostream>

template <typename T>
void foo ( T&& rgArr ) {
    typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type stripped_type;
    
    std::cout << utility::size_getter<stripped_type>().size( rgArr ) << std::endl;
}

#include <vector>
#include <array>

int main () {
    
    int c_arr0[100];
    foo(c_arr0);

    int c_arr1[200];
    foo(c_arr1);
    
    std::vector<double> double_vec( 500 );
    foo( double_vec );
    
    std::array<char, 231> char_array;
    foo( char_array );
    
}
