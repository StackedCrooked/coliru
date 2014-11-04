#include <iostream>
#include <type_traits>

#include <utility>
namespace detail {
    using std::swap;

    template<typename T>
    struct can_call_swap_impl {

        template<typename U>
        static auto check(int)
        -> decltype( swap(std::declval<T&>(), std::declval<T&>()),
                std::true_type());

        template<typename>
        static std::false_type check(...);

        using type = decltype(check<T>(0));
    };

    template<typename T>
    struct can_call_swap : can_call_swap_impl<T>::type { };
}

template<typename T>
struct is_swappable :
    std::integral_constant<bool,
        detail::can_call_swap<T>::value &&
        std::is_move_assignable<T>::value &&
        std::is_move_constructible<T>::value
    > { };

struct A
{
    A(int x) : x(x) {}
    ~A() {}
    A(const A&) = delete;
    A(A&&) = delete;
    
    friend void swap(A& rhs, A& lhs) {
        std::cout << "swapped!\n";
        using std::swap;
        swap(rhs.x, lhs.x);
    }
    
private:
    int x;
};

int main()
{
    std::cout << is_swappable<A>{} << "\n";
    
    A a(1);
    A b(2);
    using std::swap;
    swap(a, b);
}