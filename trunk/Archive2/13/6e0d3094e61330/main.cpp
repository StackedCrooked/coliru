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


namespace mob 
{ 

    template< int i, class type >
    const type &get( const std::vector< argument > &obj )
    {
        return obj[ i ].to< type >();
    }

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


class member_function
{

    public:

        template< class class_type, class ... argument_types > 
        using member_function_ptr = void ( class_type::* )( argument_types ... );

    public:

        member_function() = default;

        template< class class_type, class ... argument_types > 
        member_function( member_function_ptr< class_type, argument_types ... > fn )
        {
            m_fn = [ = ]( void *obj, const std::vector< argument > &args ){ 
                class_type *o = static_cast< class_type * >( obj );
                call( fn, o, args ); };
        }

    public:

        template< class class_type, class ... argument_types > 
        void invoke( class_type *obj, argument_types && ... args ) 
        {        
            m_fn( obj, { std::forward< argument_types >( args )... } );
        }

    private:

        template< class class_type, class ... argument_types, int ... S > 
        void call_helper( member_function_ptr< class_type, argument_types ... > fn, 
                          class_type *obj, 
                          const std::vector< argument > &args, 
                          seq< S ... > )
        {
            ( obj->*fn )( mob::get< S, argument_types >( args )... );
        }

        template< class class_type, class ... argument_types > 
        void call( member_function_ptr< class_type, argument_types ... > fn, 
                   class_type *obj, 
                   const std::vector< argument > &args )
        { 
            //if ( args.size() > m_argument_types.size() )
            //    throw std::bad_function_call();

            //for ( auto i = 0u; i < args.size(); ++i )
            //    if ( args[ i ].type() != m_argument_types[ i ] )
            //        throw std::bad_function_call();

            call_helper( fn, obj, args, typename gens< sizeof...( argument_types ) >::type() );
        }

    private:

        using function_type = 
            std::function< void( void *, const std::vector< argument > &args ) >;

        function_type m_fn = nullptr;

};


namespace mob 
{


    struct type_info
    {
        std::size_t size;    
        std::unordered_map< std::string, member_function > member_functions;
    };

    std::unordered_map< std::string, type_info * > g_type_infos;


    template< class type >
    auto get_type_info()
      -> type_info * 
    {
        static type_info * info = nullptr;

        if ( info == nullptr )
        {
            info = new type_info;
            info->size = sizeof( type );
        }

        return info;
    }


    template< class class_type, class ... argument_types >
    void register_member_function( const char * name, void ( class_type::*fn )( argument_types ... ) )
    {
        auto info = get_type_info< class_type >();
        info->member_functions.emplace( name, fn );
    }


} 

template< class class_type > 
class meta_info 
{

public:

    static 
        auto get_member_function( const char * name )
        -> member_function
    {
        const auto info = mob::get_type_info< class_type >();

        auto it = info->member_functions.find( name );

        if ( it == std::end( info->member_functions ) )
            return member_function();

        return it->second;
    }

};


#define REGISTER_TYPE( type ) mob::g_type_infos.emplace( #type, mob::get_type_info< type >() ) 
#define REGISTER_MEMBER_FUNCTION( type, mem_fn ) mob::register_member_function< type >( #mem_fn, &type::mem_fn ) 


struct dummy
{
    void foo()
    {
        std::cout << "dummy foo" << std::endl;
    }

    void bar( int value )
    {
        std::cout << value << std::endl;
    }
};

int main ()
{
    REGISTER_TYPE( dummy );
    REGISTER_MEMBER_FUNCTION( dummy, foo );
    REGISTER_MEMBER_FUNCTION( dummy, bar );
    
    // ------------------

    dummy d;

    meta_info< dummy >::get_member_function( "bar" ).invoke( &d, 21 );

    return 0;
}

