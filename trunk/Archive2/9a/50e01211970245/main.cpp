#include <type_traits>
#include <initializer_list>

void bar() {}

template<typename T>
using remove_ref_and_const = typename std::remove_const<
                                  typename std::remove_reference<T>::type
                             >::type;

int main()
{
    auto foo1 = { bar, bar, bar };
    auto foo2 = { &bar, &bar, &bar };
    
    static_assert(std::is_same<
                    remove_ref_and_const<decltype(bar)>,
                    void()>::value, "Oops1");

    static_assert(std::is_same<
                    remove_ref_and_const<decltype(&bar)>,
                    void(*)()>::value, "Oops2");
                    
    static_assert(std::is_same<
                    remove_ref_and_const<decltype(*foo1.begin())>,
                    void(*)()>::value, "Oops3");
                    
    static_assert(std::is_same<
                    remove_ref_and_const<decltype(*foo2.begin())>,
                    void(*)()>::value, "Oops4");
}
