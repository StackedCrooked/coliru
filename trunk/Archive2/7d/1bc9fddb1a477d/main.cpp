#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <iostream>
#include <array>

template <size_t i> size_t f(){
        return i;
}
 
struct Lambda
{
    Lambda(std::array<size_t, 10>& array_) : array(array_) {}
    template< typename U >
    void operator()(U x)
    {
        std::get<U::value-1>(array) = f<U::value>();
    }
    private:
        std::array<size_t, 10>& array;
};

int main(){
    std::array<size_t, 10> array;
    using range = boost::mpl::range_c<size_t, 1, 12>;
    boost::mpl::for_each<range>(Lambda(array));
    
    for(auto a : array)
        std::cout << a << std::endl;
    
    return 0;
}
