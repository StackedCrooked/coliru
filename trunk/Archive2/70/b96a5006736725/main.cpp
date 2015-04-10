#include <type_traits>
#include <typeinfo>
#include <iostream>

template<typename Value, typename... Cases>
struct switch_t
{
    using type = void;
};

template<typename Value, typename Case1, typename... Cases>
struct switch_t<Value, Case1, Cases...>
{
	using type = typename std::conditional<Value::value == Case1::value, typename Case1::type, typename switch_t<Value, Cases...>::type >::type;
};

template<typename Value, typename Then>
struct Case
{
    static const typename Value::value_type value = Value::value;
    using type = Then;
};


template<typename Value, typename... Cases>
using Switch = typename switch_t<Value, Cases...>::type;



template<int i>
using Int = std::integral_constant<int, i>;

int main()
{
        using result_type =
        Switch< Int<2>
              , Case< Int<1>, bool>
              , Case< Int<2>, float>
              , Case< Int<3>, int>
        >;

    std::cout << typeid(result_type).name() << "\n";
}
