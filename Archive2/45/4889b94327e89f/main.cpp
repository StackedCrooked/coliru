#include <type_traits>


template<typename Derived>
struct CRTP
{
    CRTP()
    {
        static_assert(std::is_base_of<CRTP, Derived>::value, "");
    }
};


struct Foo : CRTP<Foo> {};
struct Bar : CRTP<Foo> {}; // oops!


int main()
{
    Foo foo;
    Bar bar; // why no compiler error?
}
