#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>

template <typename SequenceType>
void print(const std::string & name, const SequenceType & sequence)
{
    std::cout << name << ":\n";
	for (auto e : sequence) std::cout << e << " ";
	endl(std::cout);
}

template <typename... T>
using common_type_t = typename std::common_type<T...>::type;

template <typename SequenceType>
using value_type_t = typename SequenceType::value_type;

template <typename LSequenceType, typename RSequenceType>
struct common_value_type
{
	using left_value_type = value_type_t<LSequenceType>;
	using right_value_type = value_type_t<RSequenceType>;
	using type = common_type_t<left_value_type, right_value_type>;
};

template <typename... T>
using common_value_type_t = typename common_value_type<T...>::type;

template <typename... T>
using common_vector_type_t = typename std::vector< common_value_type_t<T...> >;

template <typename LSequenceType, typename RSequenceType>
auto ifelse(bool predicate, const LSequenceType & lsequence, const RSequenceType & rsequence)
-> common_vector_type_t<LSequenceType, RSequenceType>
{
	// V is common-vector-type
	using V = common_vector_type_t<LSequenceType, RSequenceType>;
	return predicate ? V(begin(lsequence), end(lsequence)) : V(begin(rsequence), end(rsequence));
}

int main()
{
	using VI = std::vector<int>;
	using VD = std::vector<double>;

	VI x {1, 2, 3};
	print("x", x);
	VD y {11.1, 22.2, 33.3};
	print("y", y);

	bool b = true;
	auto z = ifelse(b, x, y);
	print("z", z);

	// alternatively, without defining `ifelse`
	using V = common_vector_type_t<VI, VD>;
	auto v = b ? V(begin(x), end(x)) : V(begin(y), end(y));
	print("v", v);

	return 0;
}
