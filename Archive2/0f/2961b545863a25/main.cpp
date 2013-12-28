#include <iostream>
#include <type_traits>

struct foo
{
    foo(foo const&) {}
    foo(foo&&) = delete;
};

template<class T, class = void>
struct is_move_constructible : std::false_type
{};

template<class T>
typename std::add_rvalue_reference<T>::type
create() noexcept;

template<class T>//T(create<T>()), 
struct is_move_constructible<T, decltype( T(create<T>()), void() )> : std::true_type
{};

int main()
{
    std::cout << is_move_constructible<foo>{};
}