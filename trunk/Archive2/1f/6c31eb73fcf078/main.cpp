#include<type_traits>

template <class...> struct Pack {};

// Interface
template <class, class, class = Pack<>> struct Remove_First;

template <class R, class F, class...Args1, class...Args2>
struct Remove_First<R, Pack<F, Args1...>, Pack<Args2...>> : Remove_First<R, Pack<Args1...>, Pack<Args2..., F>> {};

template <class R, class...Args1, class...Args2>
struct Remove_First<R, Pack<R, Args1...>, Pack<Args2...>>  { using type = Pack<Args2..., Args1...>; };

template <class R, class...Args>
struct Remove_First<R, Pack<>, Pack<Args...>>  { using type = Pack<Args...>; };

template <class R, class...Args1, class...Args2, class...ArgsNested>
struct Remove_First<R, Pack<Pack<ArgsNested...>, Args1...>, Pack<Args2...>> {
    using type = typename std::conditional<
	             std::is_same<typename Remove_First<R, Pack<ArgsNested...>>::type, Pack<ArgsNested...>>::value,
				 typename Remove_First<R, Pack<Args1...>, Pack<Args2..., Pack<ArgsNested...>>>::type,
				 Pack<Args2..., typename Remove_First<R, Pack<ArgsNested...>>::type, Args1...>>::type;
};

template<class R, class Pack>
using remove_first_t = typename Remove_First<R, Pack>::type;

int main() {
	using NestedPack = Pack<long, char, double, Pack<long, Pack<int, long>, short, int>, char, int>;
	static_assert(std::is_same<remove_first_t<int, NestedPack>, Pack<long, char, double, Pack<long, Pack<long>, short, int>, char, int>>::value, "Oops");
}

