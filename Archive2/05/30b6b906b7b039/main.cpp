#include <vector>
#include <type_traits>
#include <iostream>

struct Bar 
{};

struct Foo
{
    template<typename T, typename U>
    Foo(T const&, U const&) 
    {
        static_assert(std::is_same<T, Bar>::value &&
                      std::is_same<U, Bar>::value, "blah");
    }
};

void g(Foo const &) {}
void g(std::vector<Bar> const &) {}

int main()
{
    Bar a, b, c;

//    Foo foo1{1,2};  // fails static assertion

    g({1,2}); // ok
    g({a,b,c}); // ok
}
