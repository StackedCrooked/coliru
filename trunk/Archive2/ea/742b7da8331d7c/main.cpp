#include <typeindex>
 
template <typename T>
struct in_place_of {
    typedef T type;
};
 
class runtime_type {
private:
	typedef void( *throw_t )( );
	
	template <typename T>
	struct typed_throw {
		static void check( ) {
			T* garbage; // don't even need to init
			throw garbage;
		}
	};

	std::type_index index;
	throw_t check;

public:
	template <typename T>
	runtime_type( in_place_of<T> ) : index( typeid( T ) ), check( typed_throw<T>::check ) {

	}

	std::size_t hash_code( ) const {
		return index.hash_code( );
	}

	template <typename T>
	bool search ( ) const {
		try {
			check( );
		}
		catch (T* e) {
			return true;
		}
		catch (...) {
		}
		return false;
	}

	const char* name( ) const {
		return index.name( );
	}

	bool operator== ( const runtime_type& other ) const {
		return index == other.index;
	}

    bool operator!= ( const runtime_type& other ) const {
		return index != other.index;
	}

	bool operator>= ( const runtime_type& other ) const {
		return index >= other.index;
	}

	bool operator> ( const runtime_type& other ) const {
		return index > other.index;
	}

	bool operator<= ( const runtime_type& other ) const {
		return index <= other.index;
	}

	bool operator< ( const runtime_type& other ) const {
		return index < other.index;
	}

};

template <typename T>
runtime_type typeof( ) {
	typedef in_place_of<T> identity;
	return runtime_type( identity() );
}

namespace std {

	template <>
	struct hash<runtime_type> {
		size_t operator() ( const runtime_type& hashee ) {
			return hashee.hash_code( );
		}
	};

}
 
#include <iostream>
 
struct A {
    virtual ~A(){};
};

struct X {}; struct Y : A {};


 
int main() {
    
    runtime_type a = typeof<A>();
    runtime_type x = typeof<X>();
    runtime_type y = typeof<Y>();
    
    std::cout << std::boolalpha;
    std::cout << a.search<A>() << std::endl;
    std::cout << a.search<X>() << std::endl;
    std::cout << a.search<Y>() << std::endl;
    std::cout << std::endl;
    
    std::cout << x.search<A>() << std::endl;
    std::cout << x.search<X>() << std::endl;
    std::cout << x.search<Y>() << std::endl;
    std::cout << std::endl;
    
    std::cout << y.search<A>() << std::endl;
    std::cout << y.search<X>() << std::endl;
    std::cout << y.search<Y>() << std::endl;
    std::cout << std::endl;
    
}