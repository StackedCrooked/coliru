#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <functional>

#include <type_traits>

template<typename T> 
struct function_traits; 

template<typename R, typename ...Arguments>
struct function_traits<std::function<R(Arguments...)>>
{
    typedef R return_type;
	typedef std::tuple<typename std::decay<Arguments>::type...> arg_tuple;

	template<size_t N>
	struct argument
	{
		typedef typename std::tuple_element<N, std::tuple<Arguments...>>::type type;
	};
};

template<size_t N>
struct CallHelper
{
	template<typename Function, typename Tuple, typename ...Args>
	static inline auto call_helper(Function&& fun, Tuple&& t, Args&&... arguments) 
		-> decltype(CallHelper<N-1>::call_helper(std::forward<Function>(fun), 
												 std::forward<Tuple>(t), 
												 std::get<N-1>(std::forward<Tuple>(t)), 
												 std::forward<Args>(arguments)...))
	{
		return CallHelper<N-1>::call_helper(std::forward<Function>(fun), 
											std::forward<Tuple>(t), 
											std::get<N-1>(std::forward<Tuple>(t)), 
											std::forward<Args>(arguments)...);
	}
};

template<>
struct CallHelper<0>
{
	template<typename Function, typename Tuple, typename ...Args>
	static inline auto call_helper(Function&& fun, Tuple&& t, Args&&... arguments) 
		-> decltype(std::forward<Function>(fun)(std::forward<Args>(arguments)...))
	{
		return std::forward<Function>(fun)(std::forward<Args>(arguments)...);
	}
};

template<typename Function, typename Tuple>
auto call(Function&& fun, Tuple&& t)
	-> decltype(CallHelper<std::tuple_size<typename std::decay<Tuple>::type>::value>::call_helper(std::forward<Function>(fun), 
																								  std::forward<Tuple>(t)))
{
	return CallHelper<std::tuple_size<typename std::decay<Tuple>::type>::value>::call_helper(std::forward<Function>(fun), 
																							 std::forward<Tuple>(t));
}

int sum(int a, int b)
{
	return a + b;
}

int main(int argc, char* argv[])
{
	typedef std::function<int(int,int)> intAdder;
	typedef function_traits<intAdder> intAdderTraits;

    // Create with bind
	intAdder adder = std::bind(sum, std::placeholders::_1, std::placeholders::_2);
    
    // Assign a standard function pointer
    intAdder adder2 = sum;

	std::cout << "Sum is: " << call(adder, typename intAdderTraits::arg_tuple(2, 4)) << std::endl;
    std::cout << "Sum is: " << call(adder2, typename intAdderTraits::arg_tuple(3, 4)) << std::endl;

	return 0;
} 
