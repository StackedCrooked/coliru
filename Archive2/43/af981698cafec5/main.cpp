template< template< typename ... > class ... Ts >
struct unite
{
    template< typename ... T >
    struct type
        : Ts< T ... > ...
    { };
};

// This does not work as ::type does not name a type, but a template:

// template< template< typename ... > class ... Ts >
// using unite_t = typename unite< Ts ... >::type;

template< typename > struct debug_none {};
template< typename > struct debug_cout {};

template< typename ... > struct raise_demangled {};
template< typename ... > struct raise_specialized {};

template< typename, typename = int > struct match_default {};

template< template< typename ... > class Control >
void f()
{}

int main()
{
    f< unite< debug_none, raise_demangled, match_default >::type >();

    // Is there any way to create something like unite_t which works like this:
    
    // f< unite_t< debug_none, raise_demangled, match_default > >();
}
