#include <iostream>
//#include <type_traits>

template<typename Head, typename... Tail>
class tuple
		: private tuple<Tail...> {	// here is the recursion
				// Basically, a tuple stores its head (first (type/value) pair 
				// and derives from the tuple of its tail (the rest of the (type/value) pairs.
				// Note that the type is encoded in the type, not stored as data
		typedef tuple<Tail...> inherited;
	public:
		tuple() { }	// default: the empty tuple

		// Construct tuple from separate arguments:
		tuple(Head v, Tail... vtail)
			: inherited(vtail...), m_head(v) { }

		// Construct tuple from another tuple:
		template<typename... VValues>
		tuple(const tuple<VValues...>& other)
		:	 m_head(other.head()), inherited(other.tail()) { }

		template<typename... VValues>
		tuple& operator=(const tuple<VValues...>& other)	// assignment
		{
			m_head = other.head();
			tail() = other.tail();
			return *this;
		}

		Head head() { return m_head; }
		Head head() const { return m_head; }

		inherited& tail() { return *this; }
		const inherited& tail() const { return *this; }
	protected:
		Head m_head;
	};
    
class Empty {};
     
template<typename Head>
class tuple<Head> {
	public:
		tuple() { }	// default: the empty tuple

		// Construct tuple from separate arguments:
		tuple(const Head &v)
			: m_head(v) { }

		// Construct tuple from another tuple:
		template<typename Other>
		tuple(const Other& other)
		:	 m_head(other.head()) { }

		template<typename Other>
		tuple& operator=(const Other& other)	// assignment
		{
			m_head = other.head();
			return *this;
		}

		Head head() { return m_head; }
        Empty tail() { return Empty(); }

	protected:
		Head m_head;
	};

template<typename T>
void print(T t) {
    std::cout << t.head() << ' ';
    print(t.tail());
}

void print(Empty) {}

    
int main() {
    tuple<int, const char *> x(3, "hello");
    print(x);
}
    
    