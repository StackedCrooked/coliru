
namespace meta
{
    #define MAX_COUNT 64
	template<unsigned int n> struct Count { bool data[n]; };
	template<int n> struct Counter : public Counter<n-1> {};
	template<> struct Counter<0> {};

	// Create a counter
#define MAKE_COUNTER( _tag_ ) \
		static meta::Count<1> _count_ ## _tag_ (meta::Counter<1>)

	// Use counter
#define GET_COUNT( _tag_ ) \
		((sizeof(_count_ ## _tag_ (meta::Counter<MAX_COUNT + 1>())) / sizeof(bool)) - 1)
#define INC_COUNT( _tag_ ) \
		static meta::Count<GET_COUNT(_tag_) + 2> _count_ ## _tag_ (meta::Counter<GET_COUNT(_tag_) + 2>)
}


#include <iostream>

template<int i, typename a, typename T>
struct num
{
	T value;
	static void print()
	{
		std::cout << a::asName() << "." << i << "\n";
	}
};

struct DefaultName
{
    static const char* asName() { return "def"; }
};

#define NUM( _n_ , _t_ ) \
	struct str ## _n_ \
	{ \
		static const char* asName() { return #_n_ ":" #_t_; } \
	}; \
	num<GET_COUNT(_t_), str ## _n_, int> _n_; \
	INC_COUNT( _t_ )
	
    
//template<typename T>
struct Test
{
	MAKE_COUNTER( a );
	MAKE_COUNTER( b );
	
	NUM(u1, a);
	NUM(u2, a);
	NUM(v1, b);
	NUM(u3, a);
	NUM(v2, b);
	NUM(v3, b);
	NUM(u4, a);
};

int main()
{
    std::cout << "Counter test:\n";
	Test t;
	t.u1.print();
	t.u2.print();
	t.v1.print();
	t.u3.print();
	t.v2.print();
	t.v3.print();
	t.u4.print();
}