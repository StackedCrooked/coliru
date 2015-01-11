#include <type_traits>
#include <tuple>
#include <functional>

template<class T>
struct function_traits : function_traits<decltype(&T::operator())> {
};

template<class R, class... Args>
struct function_traits<R(Args...)> {
    using result_type = R;
    using argument_types = std::tuple<Args...>;
};

template<class R, class... Args>
struct function_traits<R (*)(Args...)> {
    using result_type = R;
    using argument_types = std::tuple<Args...>;
};

template<class R, class... Args>
struct function_traits<std::function<R(Args...)>> {
    using result_type = R;
    using argument_types = std::tuple<Args...>;
};

template<class T, class R, class... Args>
struct function_traits<R (T::*)(Args...)> {
    using result_type = R;
    using argument_types = std::tuple<Args...>;
};

template<class T, class R, class... Args>
struct function_traits<R (T::*)(Args...) const> {
    using result_type = R;
    using argument_types = std::tuple<Args...>;
};

template<class T>
using first_argument_type = typename std::tuple_element<0, typename function_traits<T>::argument_types>::type;

static_assert(std::is_same<first_argument_type<void(*)(int, long)>, int>{}, "Oops");
static_assert(std::is_same<first_argument_type<std::function<void (int, double)>>, int>{}, "Oops");
auto l = [](int, long) {};
static_assert(std::is_same<first_argument_type<decltype(l)>, int>{}, "Oops");
static_assert(std::is_same<first_argument_type<void(int, long)>, int>{}, "Oops");


int main(){}