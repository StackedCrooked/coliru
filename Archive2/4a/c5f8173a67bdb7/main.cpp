#include <type_traits>

struct Foo {};
struct Bar { static const Foo* _Foo; };
const Foo* Bar::_Foo = nullptr;

template <class T>
void foo_impl(const Foo* f, T*, ...) // this is general case template
{
}

// this should work only if T has static variable named _Foo with type const Foo*
template <class T>
typename std::enable_if<std::is_same<decltype(T::_Foo), const Foo*>::value>::type 
  foo_impl(const Foo* f, T*, int)
{
    T::_Foo = f;
}

template <class T>
void foo(const Foo* f) // this is general case template
{
    return foo_impl(f,(T*)nullptr, 0);
}

int main()
{
    Foo f;
    foo<Foo>( &f );
    foo<Bar>( &f );
}
