
#include <type_traits>
#include <iostream>
#include <iomanip>

template<
    class T,
	template<class> class... TraitP
>
struct and_t;

template<
	class T,
	template<class> class TraitH
>
struct and_t<T, TraitH>
	: public std::integral_constant<
		bool,
		TraitH<T>::value
	>
{};

template<
	class T,
	template<class> class TraitH,
	template<class> class... TraitP
>
struct and_t<T, TraitH, TraitP...>
	: public std::integral_constant<
		bool,
		TraitH<T>::value &&
		and_t<T, TraitP...>::value
	>
{};

template<
	template<class...> class Trait,
	class... TailP
>
struct capture {
	template<class T>
	struct inst
		: public Trait<TailP..., T>
	{};
};

// Situation

template<class Impl>
class Unit {};

class UnitExample
	: public Unit<UnitExample>
{};

template<class Impl>
struct ensure_traits
	: public and_t<
		Impl,
		// Adding template here fixed it.. oh compiler..
		capture<std::is_base_of, Unit<Impl>>::template inst
	>
{};

static_assert(
	ensure_traits<UnitExample>::value,
	"traits not satisfied for UnitExample"
);

struct Base {};
struct Derived : public Base {};

int main() {
	std::cout << std::boolalpha;
	using t_1 = and_t<
		int,
		std::is_integral,
		std::is_arithmetic
	>;
	std::cout << "t_1: " << t_1::value << "\n";

	using t_2 = and_t<
		Derived,
		capture<std::is_base_of, Base>::inst
	>;
	std::cout << "t_2: " << t_2::value << "\n";


	return 0;
}
