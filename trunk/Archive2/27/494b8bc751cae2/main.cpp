#include <type_traits>
#include <memory>
#include <cstdio>

template <class T> struct is_shared_ptr : std::false_type {};
template <class T> struct is_shared_ptr<std::shared_ptr<T> > : std::true_type {};

class Foo { };
typedef std::shared_ptr<Foo> SharedFoo;

template<class T>
void getValue(std::true_type)
{
    printf("shared!\n");
}

template<class T>
void getValue(std::false_type)
{
    printf("not shared!\n");
}

template<class T>
void getValue() {
    return getValue<T>(is_shared_ptr<T>{});
}

int main(int, char **)
{
    getValue<SharedFoo>();
    getValue<Foo>();
}
