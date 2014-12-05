#include <iostream>
#include <utility>

template <typename F, typename A>
class can_call_functor_impl
{
private:
    typedef char yes[1];
    typedef char no[2];

    template <typename U>
    static auto test(U *)
        -> decltype(void(std::declval<U const &>()(std::declval<A &>())),
                    std::declval<yes &>());

    template <typename>
    static no & test(...);

public:
    static constexpr bool value = sizeof(test<F>(0)) == sizeof(yes);
};

template <typename F>
class can_call_functor_impl<F, void>
{
private:
    typedef char yes[1];
    typedef char no[2];

    template <typename U>
    static auto test(U *)
        -> decltype(void(std::declval<U const &>()()),
                    std::declval<yes &>());

    template <typename>
    static no & test(...);

public:
    static constexpr bool value = sizeof(test<F>(0)) == sizeof(yes);
};

template <typename F, typename A>
class can_call_functor :
    public std::integral_constant<bool, can_call_functor_impl<F, A>::value> {};

class int_functor
{
public:
    void operator()(int) const;
};

#define PRINT_EXP(e) (std::cout << #e " == " << (e) << std::endl)

int main(void) {
    PRINT_EXP((can_call_functor<int_functor, int>::value));
    PRINT_EXP((can_call_functor<int_functor, short>::value));
    PRINT_EXP((can_call_functor<int_functor, void>::value));
    PRINT_EXP((can_call_functor<int_functor, double>::value));
}