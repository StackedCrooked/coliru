
#include <type_traits>

template<typename T>
void f_impl(T)
{
    static_assert(T::value, "second requirement failed to meet.");     
    T t = 10;
}   

template<typename T>
void f(T)
{
    static_assert(T(), "first requirement failed to meet.");
    f_impl(T());
}

int main()
{
    f(std::false_type{});
}
