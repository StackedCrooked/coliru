#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <iterator>
#include <stdexcept>

template <typename... nums>
int ProcessInts(nums... num)
{
	std::vector<int> v{ num... };
    std::cout << sizeof...(nums) << ": ";
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "\n";
	return sizeof...(nums);
}

template <typename R, typename... Ps, typename... Ts>
typename std::enable_if<sizeof...(Ps) == sizeof...(Ts), R>::type
apply_first_n(std::function<R(Ps...)> f, const std::vector<int> &v, Ts&&... ts)
{
	if (sizeof...(Ts) > v.size())
		throw std::out_of_range("vector too small for function");
	return f(std::forward<Ts>(ts)...);
}

template <typename R, typename... Ps, typename... Ts>
typename std::enable_if<sizeof...(Ps) != sizeof...(Ts), R>::type
apply_first_n(std::function<R(Ps...)> f, const std::vector<int> &v, Ts&&... ts)
{
    const int index = sizeof...(Ps) - sizeof...(Ts) - 1;
    static_assert(index >= 0, "incompatible function parameters");
	return apply_first_n(f, v, *(std::begin(v) + index), std::forward<Ts>(ts)...);
}

template <typename T>
std::function<T> make_fn(T *t) { return { t }; }

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    apply_first_n(make_fn(ProcessInts<int, int, int>), v);
    apply_first_n(make_fn(ProcessInts<int, int, int, int>), v);
    apply_first_n(make_fn(ProcessInts<int, int, int, int, int>), v);
    try {
        apply_first_n(make_fn(ProcessInts<int, int, int, int, int, int>), v);
    } catch (std::logic_error &e) {
        std::cout << e.what() << "\n";
    }
    
    return 0;
}