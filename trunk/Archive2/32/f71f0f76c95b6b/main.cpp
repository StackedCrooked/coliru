#include <type_traits>

void bar() {}

template<typename T>
using remove_ref_and_const = typename std::remove_const<
                                  typename std::remove_reference<T>::type
                             >::type;

int main()
{
    static_assert(std::is_same<
                    remove_ref_and_const<decltype(bar)>,
                    void()>::value, "Oops1");

    static_assert(std::is_same<
                    remove_ref_and_const<decltype(&bar)>,
                    void(*)()>::value, "Oops2");
}
