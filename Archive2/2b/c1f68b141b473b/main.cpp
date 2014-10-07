#include <iostream>
#include <string>
#include <cmath>

template<typename source_type, typename result_type = source_type>
struct square_root_functor : std::unary_function<source_type, result_type>
{
    const result_type operator() (const source_type& val) const
    {
        return static_cast<result_type>( std::sqrt( val ) );
    }
};

template<typename source_type, typename result_type = source_type, typename sqrt_func = square_root_functor<source_type, result_type> >
class square_root_proxy
{
public:
    explicit square_root_proxy( const source_type& value )
    : squared_value( value )
    {}
    
    //other operators omitted for concision
    
    bool operator>( const source_type& rhs )
    {
        return squared_value > rhs * rhs;
    }
    
    operator result_type()
    {
        return sqrt( squared_value );
    }
    
private:
    const source_type& squared_value;
    sqrt_func sqrt;
};

int main()
{
    square_root_proxy<int> S = square_root_proxy<int>(9);
    unsigned int I = 4;
    bool B = S < I;  // A
    std::cout << B << '\n';
}