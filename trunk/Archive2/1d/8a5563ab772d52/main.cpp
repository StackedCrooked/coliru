#include <vector>
#include <functional>

template<int...> struct int_sequence {};

template<int N, int... Is> struct make_int_sequence
    : make_int_sequence<N-1, N-1, Is...> {};
template<int... Is> struct make_int_sequence<0, Is...>
    : int_sequence<Is...> {};

template<int> // begin with 0 here!
struct placeholder_template
{};

#include <functional>
#include <type_traits>

namespace std
{
    template<int N>
    struct is_placeholder< placeholder_template<N> >
        : integral_constant<int, N+1> // the one is important
    {};
}


template<typename... Params>
class callback_list
{
public:
    using callback_t = std::function<void(Params...)>;

    //Overload for non-member handlers:
    void add( const callback_t& handler )
    {
        _handlers.push_back( handler );
    }

private:
    //Overload for member handlers:
    template<typename CLASS, int... Is>
    void add( CLASS& object_ref , 
              void(CLASS::*member_function)( Params... ) ,
              int_sequence<Is...> )
    {
        using namespace std::placeholders;

        _handlers.push_back( std::bind( member_function , 
                                        std::ref( object_ref ) , 
                                        placeholder_template<Is>{}...
                                      ) 
                           );
    }
public:
    template<typename CLASS>
    void add( CLASS& object_ref , 
              void(CLASS::*member_function)( Params... ) )
    {
        add( object_ref, member_function, make_int_sequence<sizeof...(Params)>{} );
    }
    

    template<typename... ARGS>
    void operator()( ARGS&&... args )
    {
        for( auto& handler : _handlers )
            handler( std::forward<ARGS>( args )... );
    } 

private:
    std::vector<callback_t> _handlers;
};


void f(int,int,int){}

struct foo
{
    void f(int,int,int){}
};

int main()
{
    using namespace std::placeholders;

    foo my_foo;
    callback_list<int,int,int> callbacks;

    callbacks.add( f );
    callbacks.add([](int,int,int){});
    callbacks.add( my_foo , &foo::f );

    callbacks(0,0,0);
}