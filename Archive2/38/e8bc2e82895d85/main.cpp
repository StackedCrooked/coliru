#include <type_traits>
#include <typeinfo>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

//-----------------------------------------------------------------------------

class some
{
    using id = size_t;

	template<typename T>
	struct type { static void id() { } };

	template<typename T>
	static id type_id() { return reinterpret_cast<id>(&type<T>::id); }

//-----------------------------------------------------------------------------

	template<typename T>
	using decay = typename std::decay<T>::type;

	template<typename T>
	using none = typename std::enable_if<!std::is_same<some, T>::value>::type;

//-----------------------------------------------------------------------------

	struct base
	{
		virtual ~base() { }
		virtual bool is(id) const = 0;
		virtual base *copy() const = 0;
	} *p = nullptr;

//-----------------------------------------------------------------------------

	template<typename T>
	struct data : base, std::tuple<T>
	{
		using std::tuple<T>::tuple;

		T       &get()      & { return std::get<0>(*this); }
		T const &get() const& { return std::get<0>(*this); }

		bool is(id i) const override { return i == type_id<T>(); }
		base *copy()  const override { return new data{get()}; }
	};

//-----------------------------------------------------------------------------

	template<typename T>
	T &get() { return static_cast<data<T>&>(*p).get(); }

	template<typename T>
	T const &get() const { return static_cast<data<T> const&>(*p).get(); }

	template<typename T>
	T &check() { return dynamic_cast<data<T>&>(*p).get(); }

	template<typename T>
	T const &check() const { return dynamic_cast<data<T> const&>(*p).get(); }

//-----------------------------------------------------------------------------

public:
	 some() { }
	~some() { delete p; }

	some(some &&s)      : p{s.p} { s.p = nullptr; }
	some(some const &s) : p{s.p->copy()} { }

	template<typename T, typename U = decay<T>, typename = none<U>>
	some(T &&x) : p{new data<U>{std::forward<T>(x)}} { }

	some &operator=(some s) { std::swap(p, s.p); return *this; }

	void clear() { delete p; p = nullptr; }

	bool empty() const { return p; }

	template<typename T> bool is() const { return p->is(type_id<T>()); }

	template<typename T> T      &&_()     && { return std::move(get<T>()); }
	template<typename T> T       &_()      & { return get<T>(); }
	template<typename T> T const &_() const& { return get<T>(); }

	template<typename T> T      &&cast()     && { return std::move(check<T>()); }
	template<typename T> T       &cast()      & { return check<T>(); }
	template<typename T> T const &cast() const& { return check<T>(); }

	template<typename T> operator T     &&()     && { return std::move(_<T>()); }
	template<typename T> operator T      &()      & { return _<T>(); }
	template<typename T> operator T const&() const& { return _<T>(); }
};


//-----------------------------------------------------------------------------

using any = some;

//-----------------------------------------------------------------------------

template<typename S, typename T>
S& operator<<(S& s, const std::vector<T>& v)
{
	for (auto& x : v)
		s << x << " ";
	return s;
}

//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	using namespace std;

//-----------------------------------------------------------------------------

	any a0 = true;
	any a1 = 'A';
	any a2 = 6;
	any a3 = 3.14;
	any a4 = "hello,";
	any a5 = std::vector<int>{6, 5, 4, 3, 2, 1, 0};
	any a6 = 2.71;
	any a7 = std::string("world!");

	cout << "* any{T}; any._<T>() :" << endl << endl;
	cout << "[0] bool        : " << a0._<bool>()             << endl;
	cout << "[1] char        : " << a1._<char>()             << endl;
	cout << "[2] int         : " << a2._<int>()              << endl;
	cout << "[3] double      : " << a3._<double>()           << endl;
	cout << "[4] const char* : " << a4._<const char*>()      << endl;
	cout << "[5] vector<int> : " << a5._<std::vector<int>>() << endl;
	cout << "[6] double      : " << a6._<double>()           << endl;
	cout << "[7] string      : " << a7._<std::string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	any c0 = a0;
	any c1 = a1;
	any c2 = a2;
	any c3 = a3;
	any c4{a4};
	any c5{a5};
	any c6{a6};
	any c7{a7};

	a0.clear();
	a1.clear();
	a2.clear();
	a3.clear();
	a4.clear();
	a5.clear();
	a6.clear();
	a7.clear();

	cout << "* any{any&}; any._<T>() :" << endl << endl;
	cout << "[0] bool        : " << c0._<bool>()             << endl;
	cout << "[1] char        : " << c1._<char>()             << endl;
	cout << "[2] int         : " << c2._<int>()              << endl;
	cout << "[3] double      : " << c3._<double>()           << endl;
	cout << "[4] const char* : " << c4._<const char*>()      << endl;
	cout << "[5] vector<int> : " << c5._<std::vector<int>>() << endl;
	cout << "[6] double      : " << c6._<double>()           << endl;
	cout << "[7] string      : " << c7._<std::string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	any m0 = std::move(c0);
	any m1 = std::move(c1);
	any m2 = std::move(c2);
	any m3 = std::move(c3);
	any m4{std::move(c4)};
	any m5{std::move(c5)};
	any m6{std::move(c6)};
	any m7{std::move(c7)};

	cout << "* any{any&&}; any._<T>() :" << endl << endl;
	cout << "[0] bool        : " << m0._<bool>()             << endl;
	cout << "[1] char        : " << m1._<char>()             << endl;
	cout << "[2] int         : " << m2._<int>()              << endl;
	cout << "[3] double      : " << m3._<double>()           << endl;
	cout << "[4] const char* : " << m4._<const char*>()      << endl;
	cout << "[5] vector<int> : " << m5._<std::vector<int>>() << endl;
	cout << "[6] double      : " << m6._<double>()           << endl;
	cout << "[7] string      : " << m7._<std::string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	std::vector<any> a(8);
	a[0] = true;
	a[1] = 'A';
	a[2] = 6;
	a[3] = 3.14;
	a[4] = "hello,";
	a[5] = std::vector<int>{6, 5, 4, 3, 2, 1, 0};
	a[6] = 2.71;
	a[7] = std::string("world!");

	cout << "* any <- T; any._<T>() :" << endl << endl;
	cout << "[0] bool        : " << a[0]._<bool>()             << endl;
	cout << "[1] char        : " << a[1]._<char>()             << endl;
	cout << "[2] int         : " << a[2]._<int>()              << endl;
	cout << "[3] double      : " << a[3]._<double>()           << endl;
	cout << "[4] const char* : " << a[4]._<const char*>()      << endl;
	cout << "[5] vector<int> : " << a[5]._<std::vector<int>>() << endl;
	cout << "[6] double      : " << a[6]._<double>()           << endl;
	cout << "[7] string      : " << a[7]._<std::string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	a[0] = m0;
	a[1] = m1;
	a[2] = m2;
	a[3] = m3;
	a[4] = m4;
	a[5] = m5;
	a[6] = m6;
	a[7] = m7;

	cout << "* any <- any&; any._<T>() :" << endl << endl;
	cout << "[0] bool        : " << a[0]._<bool>()             << endl;
	cout << "[1] char        : " << a[1]._<char>()             << endl;
	cout << "[2] int         : " << a[2]._<int>()              << endl;
	cout << "[3] double      : " << a[3]._<double>()           << endl;
	cout << "[4] const char* : " << a[4]._<const char*>()      << endl;
	cout << "[5] vector<int> : " << a[5]._<std::vector<int>>() << endl;
	cout << "[6] double      : " << a[6]._<double>()           << endl;
	cout << "[7] string      : " << a[7]._<std::string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	a[0] = std::move(m0);
	a[1] = std::move(m1);
	a[2] = std::move(m2);
	a[3] = std::move(m3);
	a[4] = std::move(m4);
	a[5] = std::move(m5);
	a[6] = std::move(m6);
	a[7] = std::move(m7);

	cout << "* any <- any&&; any._<T>() :" << endl << endl;
	cout << "[0] bool        : " << a[0]._<bool>()             << endl;
	cout << "[1] char        : " << a[1]._<char>()             << endl;
	cout << "[2] int         : " << a[2]._<int>()              << endl;
	cout << "[3] double      : " << a[3]._<double>()           << endl;
	cout << "[4] const char* : " << a[4]._<const char*>()      << endl;
	cout << "[5] vector<int> : " << a[5]._<std::vector<int>>() << endl;
	cout << "[6] double      : " << a[6]._<double>()           << endl;
	cout << "[7] string      : " << a[7]._<std::string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	auto is_double = [](const any& s) { return s.is<double>(); };
	cout << "there are "
		<< std::count_if(a.begin(), a.end(), is_double)
		<< " elements of type 'double' in vector a" << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	a0 = a[0];
	a1 = a[1];
	a2 = a[2];
	a3 = a[3];
	a4 = a[4];
	a5 = a[5];
	a6 = a[6];
	a7 = a[7];

	cout << "* type check :" << endl << endl;
	cout << "[0] is long / bool        : " << a0.is<long>() << " / " << a0.is<bool>()             << endl;
	cout << "[1] is long / char        : " << a1.is<long>() << " / " << a1.is<char>()             << endl;
	cout << "[2] is long / int         : " << a2.is<long>() << " / " << a2.is<int>()              << endl;
	cout << "[3] is long / double      : " << a3.is<long>() << " / " << a3.is<double>()           << endl;
	cout << "[4] is long / const char* : " << a4.is<long>() << " / " << a4.is<const char*>()      << endl;
	cout << "[5] is long / vector<int> : " << a5.is<long>() << " / " << a5.is<std::vector<int>>() << endl;
	cout << "[6] is long / double      : " << a6.is<long>() << " / " << a6.is<double>()           << endl;
	cout << "[7] is long / string      : " << a7.is<long>() << " / " << a7.is<std::string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	bool             &l0(a0);  l0 = false;
	char             &l1(a1);  l1 = 'B';
	int              &l2(a2);  l2 = 8;
	double           &l3(a3);  l3 = -3.14;
	const char*      &l4 = a4; l4 = "Hello,";
	std::vector<int> &l5 = a5; l5[2] = -2;
	double           &l6 = a6; l6 = -2.71;
	std::string      &l7 = a7; l7 += " ...";

	a5._<std::vector<int>>()[4] = -2;
	a7._<std::string>()[0] = 'W';

	cout << "* T&(any&); any._<T>() :" << endl << endl;
	cout << "[0] bool        : " << a0._<bool>()             << endl;
	cout << "[1] char        : " << a1._<char>()             << endl;
	cout << "[2] int         : " << a2._<int>()              << endl;
	cout << "[3] double      : " << a3._<double>()           << endl;
	cout << "[4] const char* : " << a4._<const char*>()      << endl;
	cout << "[5] vector<int> : " << a5._<std::vector<int>>() << endl;
	cout << "[6] double      : " << a6._<double>()           << endl;
	cout << "[7] string      : " << a7._<std::string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	bool             &&r0(std::move(a0));  r0 = true;
	char             &&r1(std::move(a1));  r1 = 'C';
	int              &&r2(std::move(a2));  r2 = 12;
	double           &&r3(std::move(a3));  r3 = 3.14159;
	const char*      &&r4 = std::move(a4); r4 = "HEllo,";
	std::vector<int> &&r5 = std::move(a5); r5[3] = -4;
	double           &&r6 = std::move(a6); r6 = 2.71828;
	std::string      &&r7 = std::move(a7); r7 += " !!!";

	std::move(a5)._<std::vector<int>>()[5] = -4;
	std::move(a7)._<std::string>()[1] = 'O';

	cout << "* T&&(any&&); any._<T>() :" << endl << endl;
	cout << "[0] bool        : " << a0._<bool>()             << endl;
	cout << "[1] char        : " << a1._<char>()             << endl;
	cout << "[2] int         : " << a2._<int>()              << endl;
	cout << "[3] double      : " << a3._<double>()           << endl;
	cout << "[4] const char* : " << a4._<const char*>()      << endl;
	cout << "[5] vector<int> : " << a5._<std::vector<int>>() << endl;
	cout << "[6] double      : " << a6._<double>()           << endl;
	cout << "[7] string      : " << a7._<std::string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	bool             x0{a0};
	char             x1{a1};
	int              x2{a2};
	double           x3{a3};
	const char*      x4 = a4;
	std::vector<int> x5 = a5;
	double           x6 = a6;
	std::string      x7 = a7;

	cout << "* T{any&}; T :" << endl << endl;
	cout << "[0] bool        : " << x0 << endl;
	cout << "[1] char        : " << x1 << endl;
	cout << "[2] int         : " << x2 << endl;
	cout << "[3] double      : " << x3 << endl;
	cout << "[4] const char* : " << x4 << endl;
	cout << "[5] vector<int> : " << x5 << endl;
	cout << "[6] double      : " << x6 << endl;
	cout << "[7] string      : " << x7 << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	bool             y0{std::move(a0)};
	char             y1{std::move(a1)};
	int              y2{std::move(a2)};
	double           y3{std::move(a3)};
	const char*      y4 = std::move(a4);
	std::vector<int> y5 = std::move(a5);
	double           y6 = std::move(a6);
	std::string      y7 = std::move(a7);

	cout << "* T{any&&}; T :" << endl << endl;
	cout << "[0] bool        : " << y0 << endl;
	cout << "[1] char        : " << y1 << endl;
	cout << "[2] int         : " << y2 << endl;
	cout << "[3] double      : " << y3 << endl;
	cout << "[4] const char* : " << y4 << endl;
	cout << "[5] vector<int> : " << y5 << endl;
	cout << "[6] double      : " << y6 << endl;
	cout << "[7] string      : " << y7 << endl;
	cout << endl;

}
