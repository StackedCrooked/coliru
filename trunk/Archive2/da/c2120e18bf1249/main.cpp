#include <tuple>
#include <iostream>

using namespace std;

template<int I>
struct pin_tag {};

//inputs
template<int N, class T0, class... VAR>
class inputs_base : public inputs_base<N + 1, VAR...>
{
protected:
    using inputs_base<N + 1, VAR...>::_in;
	virtual void _in(T0 const& t, pin_tag<N>) = 0;
};

template<int N, class T0>
class inputs_base<N, T0>
{
protected:
	virtual void _in(T0 const& t, pin_tag<N>) = 0;
};

template<class... VAR>
struct inputs : public inputs_base<0, VAR...>
{
	template<int N>
	using in_arg_type = typename std::tuple_element<N, std::tuple <VAR...> >::type;

	template<int N>
	void in(in_arg_type<N> const& t)
	{
		this->_in(t, pin_tag<N>());
	}
};


class test : public inputs< int, bool >
{
protected:
	virtual void _in(int const& val, pin_tag<0>)
		{cout << val << endl;}
	virtual void _in(bool const& val, pin_tag<1>)
		{cout << val << endl;}
 };

int main()
{
	test t;
	t.in<0>(100500);
	t.in<1>(true);
}