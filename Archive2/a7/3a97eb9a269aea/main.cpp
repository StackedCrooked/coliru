// http://stackoverflow.com/a/10722840

#include <type_traits>

/*! The template `has_destructor<T>` exports a
    boolean constant `value that is true iff `T` has 
    a public destructor.

    N.B. A compile error will occur if T has non-public destructor.
*/ 
template< typename T>
struct has_destructor
{   
    /* Has destructor :) */
    template <typename A> 
    static std::true_type test(decltype(std::declval<A>().~A()) *) {
        return std::true_type();
    }

    /* Has no destructor :( */
    template<typename A>
    static std::false_type test(...) {
        return std::false_type(); 
    }

    /* This will be either `std::true_type` or `std::false_type` */
    typedef decltype(test<T>(0)) type;

    static const bool value = type::value; /* Which is it? */
};

// ---

class Defined {};

template <typename T>
class vector {
};

// ---

class Defined;
int x = has_destructor<Defined>::value;

class Undefined;
int y = has_destructor<Undefined>::value;

class vector<int>;
int z = has_destructor<vector<int>>::value;

// ---

#include <iostream>
#include <vector>

int main()
{
    std::cout << z << std::endl;
    
    class vector<int>;
    std::cout << has_destructor<vector<int>>::value << std::endl;
    
    using std::vector;
    std::cout << has_destructor<vector<int>>::value << std::endl;
}