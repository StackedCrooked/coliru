#include <iostream>
#include <vector>
#include <tuple>
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


template < typename T > 
struct ValueTypeTrait
{
    typedef typename T::value_type type;
};


template < typename CheckFunctor, typename ... T  >
void grow( T... ts, const std::string& test, CheckFunctor cf )
{
    
    //ts...[0]
    //value_tuple a = std::make_tuple( ts.front() ... );
    std::vector< std::size_t > sizes = { ts.size() ... };
    
    std::cout << "str: " << test << "; " << cf( ts.front() ... , ts.back() ... ) << std::endl;
    for ( int i = 0; i < sizes.size(); i++ )
        std::cout << " " << sizes[ i ];
    std::cout << std::endl;
    
}


struct VectorCheckFunctor
{
    float operator()( int a, float b )
    {
        return a + b;
    }
    float operator()( const std::tuple< const int&, const float& >& a, const std::tuple< const int&, const float& >& b  )
    {
        return std::get< 0 >( a ) + std::get< 0 >( b )
               + std::get< 1 >( a ) + std::get< 1 >( b );
    }
    float operator()( int a1, float b1, int a2, float b2  )
    {
        return ( a1 - a2 ) + ( b1 - b2 );
    }
};

enum class PaintType
{
    A,
    B,
    C,
    D
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
    
    typedef unsigned char DataTypeT;
    DataTypeT uc1 = 100, uc2 = 110;
    auto uc1_sq = ( uc1 - uc2 ) * ( uc1 - uc2 );
    //typedef typename std::result_of< operator*(T,T) >::value QuadT;
    //typedef std::conditional< std::is_integral< DataTypeT >::value, int, DataTypeT >::type QuadT;
    //typedef std::common_type< DataTypeT, DataTypeT >::type QuadT; // DataTypeT
    typedef decltype( DataTypeT(0)-DataTypeT(0) ) QuadT;
    
    std::cout << "datatype: " << typeid( uc1 ).name() << "; " << uc1_sq << " type=" << typeid( uc1_sq ).name() << " result-of: " << typeid( QuadT ).name() << std::endl;
    
    std::vector< int > a = { 3, 2, 10, 8 };
    std::vector< float > b = { 2, 3, 4 };
    grow< VectorCheckFunctor, std::vector< int >, std::vector< float > >( a, b, "Tetest!", VectorCheckFunctor() );
    
    std::cout << "Paint type default: " << static_cast< int >( static_cast< PaintType >( 0 ) ) << std::endl;
    
    return 0;
}
