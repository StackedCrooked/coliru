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
			throw (T*)nullptr;
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

struct X {}; struct Y : A {}; struct Z : X, Y {};


 
int main() {
    
    runtime_type a = typeof<A>();
    runtime_type x = typeof<X>();
    runtime_type y = typeof<Y>();
    runtime_type z = typeof<Z>();
    
    std::cout << std::boolalpha;
    
    std::cout << "Inheritances:" << std::endl;
    std::cout << "struct A" << std::endl;
    std::cout << "struct X" << std::endl;
    std::cout << "struct Y : A" << std::endl;
    std::cout << "struct Z : Y, A" << std::endl;
    std::cout << std::endl;
    
    std::cout << "- runtime A to -" << std::endl;
    std::cout << "  A: " << a.search<A>() << std::endl;
    std::cout << "  X: " << a.search<X>() << std::endl;
    std::cout << "  Y: " << a.search<Y>() << std::endl;
    std::cout << "  Z: " << a.search<Z>() << std::endl;
    std::cout << std::endl;
    
    std::cout << "- runtime X to -" << std::endl;
    std::cout << "  A: " << x.search<A>() << std::endl;
    std::cout << "  X: " << x.search<X>() << std::endl;
    std::cout << "  Y: " << x.search<Y>() << std::endl;
    std::cout << "  Z: " << x.search<Z>() << std::endl;
    std::cout << std::endl;
    
    std::cout << "- runtime Y to -" << std::endl;
    std::cout << "  A: " << y.search<A>() << std::endl;
    std::cout << "  X: " << y.search<X>() << std::endl;
    std::cout << "  Y: " << y.search<Y>() << std::endl;
    std::cout << "  Z: " << y.search<Z>() << std::endl;
    std::cout << std::endl;
    
    std::cout << "- runtime Z to -" << std::endl;
    std::cout << "  A: " << z.search<A>() << std::endl;
    std::cout << "  X: " << z.search<X>() << std::endl;
    std::cout << "  Y: " << z.search<Y>() << std::endl;
    std::cout << "  Z: " << z.search<Z>() << std::endl;
    std::cout << std::endl;
    
}