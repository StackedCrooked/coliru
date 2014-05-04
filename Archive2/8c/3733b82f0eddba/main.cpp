#include <cstdlib>
#include <cassert>
#include <string>
#include <new>
#include <iostream>

template <typename T>
struct Alloc {
    typedef T              value_type;
	typedef T *            pointer;
	typedef const T *      const_pointer;
	typedef T &            reference;
	typedef const T &      const_reference;
	typedef std::size_t    size_type;
	typedef std::ptrdiff_t difference_type;
	template <typename U>
	  struct rebind { typedef Alloc<U> other; };
	
	
	Alloc() : instance(0) { }
	
	Alloc(int inst) : instance(inst) { }
	
	template <typename U>
	Alloc(const Alloc<U> & other) : instance(other.instance) { }
	
	Alloc & operator = (const Alloc & other) {
		if (this != &other) instance = other.instance;
	}
	
	void * allocate(size_t n, void * hint = nullptr)
		{ return malloc(n * sizeof(T)); }
		
	void deallocate(void * p, size_t)
		{ free(p); }
	int instance;
};

template <typename T, typename U>
bool operator == (const Alloc<T> & a, const Alloc<U> b)
	{ return (a.instance == b.instance); }

template <typename T, typename U>
bool operator != (const Alloc<T> & a, const Alloc<U> b)
	{ return (a.instance != b.instance); }


int main() {
	Alloc<char> alloc(1);
	std::basic_string<char, std::char_traits<char>, Alloc<char>> str("foobar", alloc);
	std::cout << str << std::endl;
	
	auto fragment = str.substr(0, 3);
	std::cout << fragment << std::endl;
	
	std::cout << str.get_allocator().instance << " "
	          << fragment.get_allocator().instance << std::endl;
	          
	assert(fragment.get_allocator() == str.get_allocator());
	return 0;
}