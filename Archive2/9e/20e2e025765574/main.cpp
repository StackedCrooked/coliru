#include <vector>
#include <iostream>
#include <functional>
#include <vector>
#include <unordered_map>


template< class type >
struct type_id_helper 
{
    static void id() { } 
};

template< class type >
constexpr std::size_t type_id() 
{ 
    return reinterpret_cast< std::size_t >( &type_id_helper< type >::id ); 
}


std::unordered_map< std::size_t, std::string > g_type_name_register;


#define REGISTER_TYPE_NAME( type ) g_type_name_register.emplace( type_id< type >(), #type );

    
class argument
{
    
    public:
    
        template< class type >
        argument( const type &data )
            : m_data( std::addressof( data ) )
            , m_type( type_id< type >() ) 
        {
        }
        
    public:
    
        template< class type >
        auto to() const 
          -> const type &
        {
            return *reinterpret_cast< const type * >( m_data );
        }
    
        auto type() const 
          -> std::size_t
        {
            return m_type;
        }
        
    private:
    
        const void *m_data;
        std::size_t m_type;
    
};


template< int i, class type >
const type &get( const std::vector< argument > &obj )
{
    return obj[ i ].to< type >();
}


template< int ... >
struct seq {};

template< int N, int ... S >
struct gens : gens< N - 1, N - 1, S... > 
{    
};

template< int ... S >
struct gens< 0, S... > 
{
    using type = seq< S ... >;
};

class function
{
    
    public:
    
        template< class ... argument_types > 
        function( void ( *fn )( argument_types ... ) )
        {
            m_fn = [ this, fn ]( const std::vector< argument > &args ){ call( fn, args ); };
            m_argument_types = { type_id< argument_types >()... };
        }
        
        template< class ... argument_types >
        auto operator=( void ( *fn )( argument_types ... ) )
          -> function &
        {
            m_fn = [ this, fn ]( const std::vector< argument > &args ){ call( fn, args ); };
            m_argument_types = { type_id< argument_types >()... };
            return *this;
        }
        
    public:
    
        template< class ... argument_types >
        void operator()( argument_types &&...args )
        {
            std::vector< argument > a = { std::forward< argument_types >( args )... };
            m_fn( a );
        }
        
    private:
    
        template< class ... argument_types, int ... S > 
        void call_helper( void ( *fn )( argument_types ... ), const std::vector< argument > &args, seq< S ... > )
        {
            fn( get< S, argument_types >( args )... );
        }
            
        template< class ... argument_types > 
        void call( void ( *fn )( argument_types ... ), const std::vector< argument > &args )
        { 
            if ( args.size() > m_argument_types.size() )
                throw std::bad_function_call();
                
                
            std::cout << "types: ";
            
            for ( const auto &arg : args )
                std::cout << g_type_name_register[ arg.type() ] << " ";
                
            std::cout << std::endl;
                
            call_helper( fn, args, typename gens< sizeof...( argument_types ) >::type() );
        }
                
    private:
    
        std::vector< std::size_t > m_argument_types;
        std::function< void( const std::vector< argument > & ) > m_fn;
    
};

void foo( int value )
{
    std::cout << "foo: " << value << std::endl;
}

void bar( int first, float second )
{
    printf( "%d %f\n", first, second );
}

int main ()
{
    REGISTER_TYPE_NAME( int );
    REGISTER_TYPE_NAME( float );
    
    function f = foo;
    
    f( 21 );
    
    f = bar;
    
    f( 3, 19.86f );
    
    return 0;
}
