// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "stdlib.h"
#include <iostream>

#include <functional> 
#include <boost/signals2.hpp>
#include <boost/bind.hpp>

template<int I>
struct pin_tag {};

//inputs
template<int N, class T0, class... VAR>
class inputs_base : public inputs_base<N + 1, VAR...>
{
protected:
    using base_type = inputs_base<N + 1, VAR...>;
	using arg_type = T0;
	using base_type::input;
	virtual void input(arg_type const& t, pin_tag<N>) = 0;
};

template<int N, class T0>
class inputs_base<N, T0>
{
protected:
	using arg_type = T0;
	virtual void input(arg_type const& t, pin_tag<N>) = 0;
};

template<class... VAR>
class inputs : public inputs_base<0, VAR...>
{
private:
	using inputs_type = inputs<VAR...>;
	using inputs_base_type = inputs_base<0, VAR...>;
	using inputs_base_type::input;

	template <int N, class T = inputs_type>
	struct getter
	{
		using next_type = getter<N - 1, typename T::base_type>;
		using arg_type = typename next_type::arg_type;
	};

	template <class T>
	struct getter<0, T>
	{
		using arg_type = typename T::arg_type;
	};

public:
	template<int N>
	using in_arg_type = typename getter<N>::arg_type;

	template<int N>
	void in(in_arg_type<N> const& t)
	{
		input(t, pin_tag<N>());
	}
};

//outputs
template<class T0, class... TT>
class outputs_base : public outputs_base<TT...>
{
protected:
	using arg_type = T0;
	using base_type = outputs_base<TT...>;
	using sig_type = boost::signals2::signal<void(arg_type const&)>;
	sig_type _out;
};

template<class T0>
class outputs_base<T0>
{
protected:
	using arg_type = T0;
	using sig_type = boost::signals2::signal<void(arg_type const&)>;
	sig_type _out;
};

template<class... TT>
class outputs : public outputs_base<TT...>
{
private:
	using outputs_type = outputs<TT...>;

	template <int N, class T = outputs_type>
	struct getter
	{
		using next_type = getter<N - 1, typename T::base_type>;
		using sig_type = typename next_type::sig_type;
		using cur_outputs_type = typename next_type::cur_outputs_type;
	};

	template <class T>
	struct getter<0, T>
	{
		using sig_type = typename T::sig_type;
		using cur_outputs_type = T;
	};
public:
	template<int N>
	typename getter<N>::sig_type& out()
	{
		return getter<N>::cur_outputs_type::_out;
	}
};

template<class INPUTS, class OUTPUTS>
class block : public INPUTS, public OUTPUTS {};

template<int OUT, int IN, class BLOCK_OUT, class BLOCK_IN>
void block_connect(BLOCK_OUT& block_out, BLOCK_IN& block_in)
{
	block_out.template out<OUT>().connect(boost::bind(&BLOCK_IN::template in<IN>, &block_in, _1));
}

//////////////////////////////////////////////////////////////////////////////////////

class test_block1 : public block< inputs<bool>, outputs<bool, int, float> >
{
protected:
	virtual void input(bool const& val, pin_tag<0>)
	{

	}
public:
	void test_shot()
	{
		out<1>()(100500);
		out<0>()(false);
	}
};

class test_block2 : public block< inputs<int, bool, int>, outputs<float> >
{
protected:
	virtual void input(int const& val, pin_tag<0>)
	{
		std::cout << "test_block2::input0: " << val << std::endl;
	}
	virtual void input(bool const& val, pin_tag<1>)
	{
		std::cout << "test_block2::input1: " << std::boolalpha << val << std::endl;
	}
	virtual void input(int const& val, pin_tag<2>)
	{
		std::cout << "test_block2::input2: " << val << std::endl;
	}
};

int main()
{
	test_block1 tb1;
	test_block2 tb2;

	block_connect<1, 2>(tb1, tb2);
	block_connect<0, 1>(tb1, tb2);


	tb1.test_shot();
	
	//system("pause");
	return 0;
}

