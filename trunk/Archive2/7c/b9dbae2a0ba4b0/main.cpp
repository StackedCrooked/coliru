#include <iostream>
#include <vector>
#include <typeinfo>

template < typename T >
struct Base
{
    T d1, d2;
    
    template < typename TT >
    Base< TT > cast() { return { static_cast< TT >( d1 ), static_cast< TT >( d2 ) }; }
};

template < typename T >
struct Child : public Base< T >
{
    T D1() { return this->d1; }
};


int main()
{
    std::vector< int > test; 
    test.reserve( 100 );
    std::cout << "capacity: " << test.capacity() << std::endl;
    test.clear();
    std::cout << "capacity: " << test.capacity() << std::endl;
    
    Base< float > base = { 0.5f, 10.4f };
    
    //Child< int > 
    std::cout << base.cast< int >().d2 << std::endl;
    
    typedef short DataTypeT;
    DataTypeT uc1 = 100;
    auto uc1_sq = uc1 * uc1;
    //typedef typename std::result_of< operator*(T,T) >::value QuadT;
    //typedef std::conditional< std::is_integral< DataTypeT >::value, int, DataTypeT >::type QuadT;
    typedef std::common_type< DataTypeT, DataType >::type QuadT;
    
    std::cout << "datatype: " << typeid( uc1 ).name() << "; " << uc1_sq << " type=" << typeid( uc1_sq ).name() << " result-of: " << typeid( QuadT ).name() << std::endl;
    
    return 0;
}
