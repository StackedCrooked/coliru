
#include <iostream>


namespace detail {

template<typename T>
static constexpr auto hasTest(const T&) -> decltype(std::declval<T>().test(), std::true_type());

template<typename>
static constexpr std::false_type hasTest(...);


template<typename T>
void test_impl(const T& t, std::true_type)
{
    std::cout << "volam test()...\n";
	t.test();
}

template<typename T>
void test_impl(const T& t, std::false_type)
{
	std::cout << "nic\n";
}

} // namespace detail {


template<typename T>
void test(const T& t)
{
	using has_test = decltype(detail::hasTest<T>(t));
	detail::test_impl(t, has_test());
}

// ---------------------------------------------------------------------------

struct Pokus1
{
};

struct Pokus2
{
	void test() const
	{
		std::cout << "test\n";
	}
};

int main()
{
	test(Pokus1());

	std::cout << "------\n";

	test(Pokus2());

	return 0;
}

