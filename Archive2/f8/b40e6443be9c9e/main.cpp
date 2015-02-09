#define BOOST_RESULT_OF_USE_TR1 1

#include <boost/utility/result_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/typeof/typeof.hpp>

struct A {};
struct B {};
struct C {};

template <class H> class foo_B_A {
    H handler_;
public:
  typedef bool result_type;
  foo_B_A (H h) : handler_ (h) {}
  bool operator() (B) const { return handler_ (A ()); }
};

template <class H> class foo_C_B {
	H handler_;
public:
  typedef bool result_type;
  foo_C_B (H h) : handler_ (h) {}
  bool operator() (C) const { return handler_ (B ()); }
};

template <typename H>
foo_B_A<H>
foo (H h, typename boost::enable_if<
  boost::is_same<typename boost::result_of<H(A)>::type, bool> >::type* = 0)
{
	return foo_B_A<H> (h);
}

template <typename H>
foo_C_B<H>
foo (H h, typename boost::enable_if<
  boost::is_same<typename boost::result_of<H(B)>::type, bool> >::type* = 0)
{
	return foo_C_B<H> (h);
}

struct fooify
{
	template <class> struct result {};
	template <class F, class T> struct result<F(T)>
	{
		typedef BOOST_TYPEOF_TPL (foo (boost::declval<T> () ())) type;
	};

	template <typename T>
	BOOST_TYPEOF_TPL (foo (boost::declval<T> () ()))
	// auto
	operator() (T t) const // -> decltype (foo (t))
	{ return foo (t); }
};

template <class Action, class Stop, class Arg, class=void>
struct repeat_until_helper
{
	typedef typename boost::result_of<Action (Arg)>::type action_result;

	template <class> struct result{};
	template <class F> struct result<F(Action,Arg)> {
    typedef typename boost::result_of<
      repeat_until_helper <Action, Stop, action_result> (Action, action_result)
    >::type type;
	};

	typename boost::result_of<
	  repeat_until_helper <Action, Stop, action_result> (Action, action_result)
	>::type operator() (Action action, Arg arg) const
	{
		return repeat_until_helper <Action, Stop, action_result> ()
		  (action, action (arg));
  }
};

template <typename Action, class Stop, class Arg>
struct repeat_until_helper<Action, Stop, Arg,
  typename boost::enable_if<
    boost::is_same<typename boost::result_of<Arg (Stop)>::type, bool>
  >::type>
{
	template <class> struct result {};
	template <class F> struct result<F(Action,Arg)> {
		typedef Arg type;
  };

	Arg operator() (Action action, Arg arg) const { return arg; }
};


template <class Stop, class Action, class Arg>
typename boost::result_of<
    repeat_until_helper <Action, Stop, Arg> (Action, Arg)
>::type repeat_until (Action action, Arg arg)
{
	return repeat_until_helper<Action, Stop, Arg> () (action, arg);
}

struct InnerHandler
{
	typedef bool result_type;
	bool operator() (A) const { return false; }
};

int main ()
{
	InnerHandler inner_handler = InnerHandler ();
	// auto f = foo (foo (foo (foo ( inner_handler ))));
	// repeat_until<C> ( fooify (), inner_handler ) ( C () );
	repeat_until_helper<fooify, C, InnerHandler> ()
	  ( fooify (), inner_handler ) ( C () );
}
