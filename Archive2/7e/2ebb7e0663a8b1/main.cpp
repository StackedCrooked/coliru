template < typename FN > struct foo
{
    static constexpr int bar() { return fn(100) ; }

    constexpr int baz() const { return fn(100) ; }

    static constexpr FN fn {} ;
};

struct functor
{
   constexpr int operator() ( int a ) const { return a + 56 ; }
};

#include <iostream>
#include <type_traits>

int main()
{
     constexpr foo<functor> object ;

     std::integral_constant< int, foo<functor>::bar() + object.baz() > c ;
     std::cout << "value of c is: " << c << ' ' ;

     const functor& ref_functor = foo<functor>::fn ;
     std::cout << " and value of ref_functor(100) is: " << ref_functor(100) << '\n' ;

#ifdef TAKE_ITS_ADDRESS
     std::cout << "address is: " << std::addressof( foo<functor>::fn ) << '\n' ;
#endif // TAKE_ITS_ADDRESS
}

#ifdef DEFINE_IT
template < typename FN > constexpr FN foo<FN>::fn ;
#endif // DEFINE_IT
