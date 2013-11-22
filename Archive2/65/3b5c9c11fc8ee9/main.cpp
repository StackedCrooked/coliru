#include <iostream>
#include <string>
#include <type_traits>

#define EXTENDED_USING_SYNTAX
#ifdef NO_EXTENDED_USING_SYNTAX
template<typename T>
struct add_const_reference {
    typedef 
        typename std::add_lvalue_reference<
            typename std::add_const<T>::type
        >::type
    type;
};
#else
#if 0
template<typename T>
struct add_const_reference {
    using type =
        typename std::add_lvalue_reference<
            typename std::add_const<T>::type
        >::type;
};
#else
template<typename T>
class add_const_reference {
    using const_T = typename std::add_const<T>::type;
    using ref_const_T = typename std::add_lvalue_reference<const_T>::type;
public:
    using type = ref_const_T;
};
#endif
#endif

template<typename... Ts>
class tuple {};
    
template<typename Head, typename... Tail>
class tuple<Head, Tail...>
	: private tuple<Tail...> {	// here is the recursion
			// Basically, a tuple stores its head (first (type/value) pair 
			// and derives from the tuple of its tail (the rest of the (type/value) pairs.
			// Note that the type is encoded in the type, not stored as data
	typedef tuple<Tail...> inherited;
public:
	tuple() { }	// default: the empty tuple

	// Construct tuple from separate arguments:
	tuple(typename add_const_reference<Head>::type v, typename add_const_reference<Tail>::type... vtail)
		: inherited(vtail...), m_head(v) { }

	// Construct tuple from another tuple:
	template<typename... VValues>
	tuple(const tuple<VValues...>& other)
	:	 inherited(other.tail()), m_head(other.head()) { }

	template<typename... VValues>
	tuple& operator=(const tuple<VValues...>& other)	// assignment
	{
		m_head = other.head();
		tail() = other.tail();
		return *this;
	}

	typename add_const_reference<Head>::type head() { return m_head; }
	typename add_const_reference<const Head>::type head() const { return m_head; }

	inherited& tail() { return *this; }
	const inherited& tail() const { return *this; }
protected:
	Head m_head;
};

template<typename T>
void print(T &&arg) {
    std::cout << arg;
}

void print(const std::string &arg) {
    std::cout << '"' << arg << '"';
}

template<typename... Ts>
void print_tuple_helper(const tuple<Ts...> &t) {
    print(t.head());
    std::cout << ',';
    print_tuple_helper(t.tail());
}

template<typename T>
void print_tuple_helper(const tuple<T> &t) {
   print(t.head());
 }

template<typename... Ts>
void print_tuple(const tuple<Ts...> &t) {
    std::cout << '(';
    print_tuple_helper(t);
    std::cout << ')';
}
    
    
    
int main() {
    tuple<int, std::string, double> t{42, "hello, world", 3.14};
    print_tuple(t);
}

