#include <type_traits>

template<class T>
struct A
{
    void test() const
	{
	static_assert( std::is_same<T, double>::value, "" );
	}

	template<class U> friend A fun()
	{
	    return A();
	}
};

int main()
{
	A<double> aa; // 1
	(void)aa;
	const auto& a = fun<int>();
	a.test();
}
