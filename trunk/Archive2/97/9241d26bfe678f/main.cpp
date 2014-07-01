#include<type_traits>

template<typename T> class Wrap;

template<typename T>
using WrapRet = typename std::enable_if<std::is_class<T>::value, Wrap<T>>::type;

template<typename T>
WrapRet<T> make_wrapper( T i )
{
    return Wrap<T>( i );
}

template<typename T>
class Wrap : T
{
    friend WrapRet<T> make_wrapper<T>( T );
private:
    Wrap( T v ) : T( v ) {}
};

template<typename T>
class Imp
{
    T x;
public:
    Imp( T v ) {}
};

int main()
{
    auto wrap = make_wrapper( Imp<int>( 1 ) );
    return 0;
}
