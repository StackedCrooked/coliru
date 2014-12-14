#include <type_traits>


template<typename Derived>
struct CRTP
{
    CRTP()
    {
        static_assert(std::is_base_of<CRTP, Derived>::value, "");
    }
};


struct Foo {};
struct Bar : CRTP<Foo> {}; // oops!


int main()
{
    Bar bar;
}
