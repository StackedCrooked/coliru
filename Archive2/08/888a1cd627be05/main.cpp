#include <tuple>

template<typename T> class Foo {};

template<typename R, typename C, typename... A>
class Foo<R(C, A...)> {};

template<typename R, typename C, typename... A> 
R deduce_R_type(R(C::*)(A...));

template<typename R, typename C, typename... A>
C deduce_C_type(R(C::*)(A...));

template<typename R, typename C, typename... A>
std::tuple<A...> deduce_A_tuple(R(C::*)(A...));

template<typename R, typename C, typename T>
struct FooHelper;

template<typename R, typename C, typename... A>
struct FooHelper< R, C, std::tuple<A...> >
{
    typedef Foo< R( C, A... ) > type;
};

struct SomeClass
{
    int SomeFunction( int, double, SomeClass* );
};

int main()
{
FooHelper< decltype(deduce_R_type(&SomeClass::SomeFunction)),
           decltype(deduce_C_type(&SomeClass::SomeFunction)), 
           decltype(deduce_A_tuple(&SomeClass::SomeFunction)) >::type instance;
}
