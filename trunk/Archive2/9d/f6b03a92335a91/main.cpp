#include <iostream>
#include <type_traits>

void bar() {std::cout << __PRETTY_FUNCTION__ << '\n';}

template<typename T>
using remove_ref_and_const = typename std::remove_reference<typename std::remove_const<T>::type>::type;

int main()
{
    {
        auto foo = {bar, bar, bar};
        static_assert(std::is_same<
                        remove_ref_and_const<decltype(bar)>,
                        void()>::value, "Oops1");
    }
    {
        auto foo = {&bar, &bar, &bar};
        static_assert(std::is_same<
                        remove_ref_and_const<decltype(&bar)>,
                        void(*)()>::value, "Oops2");
    }
}
