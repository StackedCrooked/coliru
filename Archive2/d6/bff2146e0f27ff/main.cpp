#include <iostream>

using namespace std;

template<int I>
struct pin_tag {};

//inputs
template<int N, class T, class... U>
class inputs_base : public inputs_base<N + 1, U...>
{
protected:
    using inputs_base<N + 1, U...>::_in;
	virtual void _in(T const& t, pin_tag<N>) = 0;
};

template<int N, class T>
class inputs_base<N, T>
{
protected:
	virtual void _in(T const& t, pin_tag<N>) = 0;
};

template<class... U>
struct inputs : public inputs_base<0, U...>
{
	template<int N, typename T>
	void in(T const& t) { this->_in(t, pin_tag<N>()); }
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