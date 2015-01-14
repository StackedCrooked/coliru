#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

template<class T>
struct Null_Function{
    const T& operator()(const T& t)const{
		return t;
	}
};

template <typename Iterator, typename Func = Null_Function<typename std::iterator_traits<Iterator>::value_type>>
typename std::enable_if<
	 	   std::is_const<Iterator>::value,
		   typename std::iterator_traits<Iterator>::value_type>::type
		   Median(Iterator src_begin, Iterator src_end, Func func = Func()) {
		using value_type = typename std::iterator_traits<Iterator>::value_type;
		size_t count = std::distance(src_begin, src_end);
		std::nth_element(src_begin, src_begin + (count / 2), src_cpy_end,
			[&](value_type a, value_type b) { return func(a) < func(b); });
		return count > 0 ? func(*(src_begin + (count / 2))) : 0;
}

template <typename ConstIterator, typename Func = Null_Function<typename std::iterator_traits<ConstIterator>::value_type>>
typename std::enable_if<
		 !std::is_const<ConstIterator>::value,
		 typename std::iterator_traits<ConstIterator>::value_type>::type
	 Median(ConstIterator src_begin, ConstIterator src_end, Func func = Func()) {
		using value_type = typename std::iterator_traits<ConstIterator>::value_type;
		std::vector<value_type> src_cpy(src_begin, src_end);
		auto src_cpy_begin = src_cpy.begin();
		auto src_cpy_end = src_cpy.end();

		size_t count = std::distance(src_cpy_begin, src_cpy_end);
		std::nth_element(src_cpy_begin, src_cpy_begin + (count / 2), src_cpy_end,
			[&](value_type a, value_type b) { return func(a) < func(b); });
		return count >0 ? func(*(src_cpy_begin + (count / 2))) : 0;
}

int main()
{
	const std::vector<double> arr = { 5, 2, 32, 11, 7, 8, 9 };
	std::cout << Median(arr.begin(), arr.end());//use second overload slower

	std::vector<double> arr2 = { 5, 2, 32, 11, 7, 8, 9 };
	std::cout << Median(arr2.begin(), arr2.end());//use first overload (find median inplace ) faster
}