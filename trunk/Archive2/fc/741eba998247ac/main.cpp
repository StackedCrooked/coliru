#include <type_traits>

template <typename T, typename... Args>
struct is_only_constructible
{
    template <typename U, typename=void>
    struct test : std::false_type {};
    template <typename U>
    struct test<U, decltype(void(new U(std::declval<Args>()...)))>
        : std::true_type {};
    
    static constexpr bool value = test<T>::value;
};

class A { ~A(); public: A(int); };

int main()
{
    static_assert( is_only_constructible<A, int>::value, "" );   
}


