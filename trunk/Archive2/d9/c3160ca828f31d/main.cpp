#include <iostream>

namespace 
{
    template<size_t _current, typename... _Elements>
	struct variadic;

	template<typename Head, typename... _Elements>
	struct variadic<0, Head, _Elements...>
	{
		template<size_t index, typename T>
		struct index_of;
		
		template<size_t index>
		struct index_of<index, Head> 
		{ 
			static constexpr size_t value = 0;
		};
		
		template<size_t index>
		struct at
		{
            static_assert(index == 0, "type not found");
			typedef Head type;
		};
	};

	template<size_t _current, typename Head, typename... _Elements>
	struct variadic<_current, Head, _Elements...>
	{
		typedef typename variadic<_current-1, _Elements...>::Head head_type;
		
		template<size_t index, typename T>
		struct index_of 
		{ 
			static constexpr size_t value = index_of<index-1, T>::value;
		};
		template<size_t index>
		struct index_of<index, head_type> 
		{ 
			static constexpr size_t value = _current;
		};
		
		template<size_t index, typename TResult = head_type>
		struct at
		{
			typedef typename variadic<_current-1, _Elements...>::template at<index>::type type;
		};
		
		template<typename TResult>
		struct at<_current, TResult>
		{
			typedef head_type type;
		};
	};
}

template<typename T, typename... TArgs>
struct index_of 
{
	static constexpr size_t value = variadic<sizeof...(TArgs) - 1, TArgs...>::template index_of<T>::value;
};

template<size_t index, typename... TArgs>
struct at
{
	typedef variadic<sizeof...(TArgs) - 1, TArgs...>::template typename at<index>::type type;
};
template<size_t index, typename... TArgs> using at_t = at<index, TArgs...>::type;
 
int main()
{
   at<2, int, char, bool>::type x = true;
   std::cout << x;
}