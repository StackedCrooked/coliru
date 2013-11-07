#include <ostream>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <stdexcept>
#include <cassert>

#include <iostream>
#include <string>
#include <utility>
#include <tuple>

// For generic types, directly use the result of the signature of its 'operator()'
template<typename T>
struct function_traits
    : public function_traits<decltype(&T::operator())>
{
};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
// we specialize for pointers to member function
{
    // arity is the number of arguments.
    static const int arity = (sizeof...(Args));

    using return_type = ReturnType;

    template<size_t i>
    struct arg
    {
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
        using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };
};

#include <functional>

namespace std 
{
    template<typename T, T... I>
    struct integer_sequence 
    {
        typedef T value_type;

        static constexpr size_t size() noexcept { return sizeof...(I); }
    };
    
    template<typename T, int N, int... S>
    struct gen_integer_sequence : gen_integer_sequence<T, N-1, N-1, S...>
    {
    };

    template<typename T, int... S>
    struct gen_integer_sequence<T, 0, S...> 
    {
        typedef integer_sequence<T, S...> type;
    };

    template<typename T, T N>
    using make_integer_sequence = typename gen_integer_sequence<T, N>::type;

}  // namespace std

// This function doesn't need a body, it should never be called, and should be hidden internally.
template<typename CALLABLE, typename T, T... S>
auto convert_to_std_function(std::integer_sequence<T, S...>) ->
std::function<typename function_traits<CALLABLE>::return_type(typename function_traits<CALLABLE>::template arg<S>::type...)>;

template<typename CALLABLE>
struct std_function_convert
{
    using type = decltype(convert_to_std_function<CALLABLE>(typename std::make_integer_sequence<size_t, function_traits<CALLABLE>::arity>()));
};

// test code below:
int main()
{
    auto lambda = [](int i) { return long(i*10); };

    using traits = function_traits<decltype(lambda)>;
    
    using std_function = std_function_convert<decltype(lambda)>::type;
    std_function lf = lambda;
    
    static_assert(std::is_same<std_function, std::function<long(int)>>::value, "err1");
    static_assert(std::is_same<long, traits::return_type>::value, "err2");
    static_assert(std::is_same<int, traits::arg<0>::type>::value, "err3");

    return 0;
}