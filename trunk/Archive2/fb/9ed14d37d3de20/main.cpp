#include <utility>
#include <tuple>
#include <iostream>

//-----------------------------------------------------------------------------

namespace op
{
    struct lt
	{
		template<typename A, typename B>
		auto operator()(A&& a, B&& b) const
		-> decltype(std::forward<A>(a) < std::forward<B>(b))
			{ return std::forward<A>(a) < std::forward<B>(b); }
	};

	struct gt
	{
		template<typename A, typename B>
		auto operator()(A&& a, B&& b) const
		-> decltype(std::forward<A>(a) > std::forward<B>(b))
			{ return std::forward<A>(a) > std::forward<B>(b); }
	};

	struct eq
	{
		template<typename A, typename B>
		auto operator()(A&& a, B&& b) const
		-> decltype(std::forward<A>(a) == std::forward<B>(b))
			{ return std::forward<A>(a) == std::forward<B>(b); }
	};

	struct ne
	{
		template<typename A, typename B>
		auto operator()(A&& a, B&& b) const
		-> decltype(std::forward<A>(a) != std::forward<B>(b))
			{ return std::forward<A>(a) != std::forward<B>(b); }
	};

	struct le
	{
		template<typename A, typename B>
		auto operator()(A&& a, B&& b) const
		-> decltype(std::forward<A>(a) <= std::forward<B>(b))
			{ return std::forward<A>(a) <= std::forward<B>(b); }
	};

	struct ge
	{
		template<typename A, typename B>
		auto operator()(A&& a, B&& b) const
		-> decltype(std::forward<A>(a) >= std::forward<B>(b))
			{ return std::forward<A>(a) >= std::forward<B>(b); }
	};

}

//-----------------------------------------------------------------------------

template<typename T>
struct relational
{
    // cast to base/derived class
	static const relational&
	base(T const& a) { return static_cast <const relational&>(a); }

	const T& der() const { return static_cast<const T&>(*this); }

	// interface: relational operators
	friend bool operator< (T const &a, T const &b) { return base(a).compare(op::lt(), b); }
	friend bool operator> (T const &a, T const &b) { return base(a).compare(op::gt(), b); }
	friend bool operator==(T const &a, T const &b) { return base(a).compare(op::eq(), b); }
	friend bool operator!=(T const &a, T const &b) { return base(a).compare(op::ne(), b); }
	friend bool operator<=(T const &a, T const &b) { return base(a).compare(op::le(), b); }
	friend bool operator>=(T const &a, T const &b) { return base(a).compare(op::ge(), b); }

	// private dispatcher, to be called by relational operators
	template<typename F>
	bool compare(F f, T const &b) const { return der().comp(f, b); }

protected:
	// protected implementation, possibly overriden, to be called by compare
	bool comp(op::gt, T const &b) const { return b < der(); }
	bool comp(op::eq, T const &b) const { return !(der() < b || der() > b); }
	bool comp(op::ne, T const &b) const { return !(b == der()); }
	bool comp(op::le, T const &b) const { return !(b < der()); }
	bool comp(op::ge, T const &b) const { return !(der() < b); }
};

//-----------------------------------------------------------------------------

template<typename... T>
class direct : std::tuple<T...>, public relational<direct<T...>>
{
	friend relational<direct>;
	using U = std::tuple<T...>;

	const U& tup() const { return static_cast<const U&>(*this); }

	// override all functions
	template<typename F>
	bool comp(F, const direct &b) const { return F()(tup(), b.tup()); }

public:
	using std::tuple<T...>::tuple;
};

//-----------------------------------------------------------------------------

#define LAZY 0
#if LAZY

template<typename... T>
class reverse : std::tuple<T...>, public relational<reverse<T...>>
{
	friend relational<reverse>;
	using relational<reverse>::comp;
	using U = std::tuple<T...>;

	const U& tup() const { return static_cast<const U&>(*this); }

	// override operator< only, rest is automatically generated
	bool comp(op::lt, const reverse &b) const { return tup() > b.tup(); }

public:
	using std::tuple<T...>::tuple;
};

#else  // LAZY

template<typename... T>
class reverse : std::tuple<T...>, relational<reverse<T...>>
{
	friend relational<reverse>;

	using U = std::tuple<T...>;

	const U& tup() const { return static_cast<const U&>(*this); }

	// override all functions (in fact, only == and !=)
	template<typename F>
	bool comp(F, const reverse &b) const { return F()(tup(), b.tup()); }

    // override remaining functions, each separately
    bool comp(op::lt, const reverse &b) const { return tup() >  b.tup(); }
	bool comp(op::gt, const reverse &b) const { return tup() <  b.tup(); }
	bool comp(op::le, const reverse &b) const { return tup() >= b.tup(); }
	bool comp(op::ge, const reverse &b) const { return tup() <= b.tup(); }

public:
	using std::tuple<T...>::tuple;
};

#endif  // LAZY

//-----------------------------------------------------------------------------

int main ()
{
	direct <int,int> n1{5,2}, n2{6,1}, n3{6,5}, n4{6,5};
	reverse<int,int> r1{5,2}, r2{6,1}, r3{6,5}, r4{6,5};

	std::cout << (n1 > n2) << " " << (n2 >= n3) << " " << (n3 >= n4) << std::endl;  // 0 0 1
	std::cout << (r1 > r2) << " " << (r2 >= r3) << " " << (r3 >= r4) << std::endl;  // 1 1 1
}
