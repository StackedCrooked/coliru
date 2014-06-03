// Extended answer to http://stackoverflow.com/a/23954589/89999
// Now handles tuple, vector, set, initializer_list
// (though it only proves a tuple with all the same type)

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <tuple>

//
// ProcessInts<...> - show that the correct arguments were received.
//
template <typename... nums>
int ProcessInts(nums... num)
{
	std::vector<int> v{ num... };
    std::cout << sizeof...(nums) << ": ";
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "\n";
	return sizeof...(nums);
}

// is_zero<N> - flag helper to select correct overload
template <int> struct is_zero    : std::false_type {};
template <>    struct is_zero<0> : std::true_type  {};

//
// func_info<F> - type-traits style with values:
//   return_type - similar to std::result_of<F>::type
//   params_tuple - a tuple with the same types as F accepts
//   params_count - integer with length matching count of params_tuple
// note: no provision is made for variadic functions
template <typename F, typename...Ps>
struct func_info {};

template <typename R, typename...Ps>
struct func_info<R(Ps...)>
{
    using return_type = R;
    using params_tuple = std::tuple<Ps...>;
    static const int params_count = sizeof...(Ps);
};

template <typename R, typename...Ps>
struct func_info<R(*)(Ps...)>
{
    using result_type = R;
    using params_tuple_type = std::tuple<Ps...>;
    static const int params_count = sizeof...(Ps);
};

template <typename R, typename...Ps>
struct func_info<R(&)(Ps...)>
{
    using result_type = R;
    using params_tuple_type = std::tuple<Ps...>;
    static const int params_count = sizeof...(Ps);
};

template <typename R, typename...Ps>
struct func_info<R(*&)(Ps...)>
{
    using result_type = R;
    using params_tuple_type = std::tuple<Ps...>;
    static const int params_count = sizeof...(Ps);
};

//
// apply_first_n
//   std::true_type indicates we're done unpacking; call the function!
template <typename F, typename C, typename... Ts>
typename func_info<F>::result_type
apply_first_n(std::true_type, F&& f, const C&, Ts&&... ts)
{
	return f(std::forward<Ts>(ts)...);
}

//   std::false_type means there's more work; get the next parameter from the container
template <typename F, typename C, typename... Ts>
typename func_info<F>::result_type
apply_first_n(std::false_type, F&& f, const C &c, Ts&&... ts)
{
    const int index = func_info<F>::params_count - sizeof...(Ts) - 1;
    auto it = std::begin(c);
    std::advance(it, index);
    return apply_first_n(is_zero<index>{}, f, c, *it, std::forward<Ts>(ts)...);
}

//   std::false_type means there's more work; get the next parameter from the tuple
template <typename F, typename... Cs, typename... Ts>
typename func_info<F>::result_type
apply_first_n(std::false_type, F&& f, const std::tuple<Cs...> &c, Ts&&... ts)
{
    const int index = func_info<F>::params_count - sizeof...(Ts) - 1;
    return apply_first_n(is_zero<index>{}, f, c, std::get<index>(c), std::forward<Ts>(ts)...);
}

//    no tag - entry point for container classes; ensures runtime size is large enough
template <typename F, typename C>
typename func_info<F>::result_type
apply_first_n(F&& f, const C &c)
{
    const size_t params_count = func_info<F>::params_count;
    if (params_count > c.size())
		throw std::out_of_range("container doesn't contain enough arguments");

    return apply_first_n(is_zero<params_count>{}, f, c);
}

//    no tag - specialized entry point for tuples, as they lack .size()
template <typename F, typename... Cs>
typename func_info<F>::result_type
apply_first_n(F&& f, const std::tuple<Cs...> &c)
{
    const size_t params_count = func_info<F>::params_count;
    if (params_count > sizeof...(Cs))
    	throw std::out_of_range("container doesn't contain enough arguments");

    return apply_first_n(is_zero<params_count>{}, f, c);
}


int main()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    std::set<int> s{1, 2, 3, 4, 5};
    auto t = std::make_tuple(1, 2, 3, 4, 5);
    auto i { 1, 2, 3, 4, 5 };
    apply_first_n(ProcessInts<>, v);
    apply_first_n(ProcessInts<int>, s);
    apply_first_n(ProcessInts<int, int, int>, t);
    apply_first_n(ProcessInts<int, int, int, int>, s);
    apply_first_n(ProcessInts<int, int, int, int, int>, i);
    try {
        apply_first_n(&ProcessInts<int, int, int, int, int, int>, v);
    } catch (std::logic_error &e) {
        std::cout << e.what() << "\n";
    }
    
    return 0;
}