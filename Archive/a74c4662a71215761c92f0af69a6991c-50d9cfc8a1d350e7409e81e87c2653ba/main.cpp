#include <tuple>
#include <utility>
#include <type_traits>
#include <iostream>

template <typename T>
struct default_get {
	T operator () ( T& current ) {
		return current;
	}
};

template <typename T>
struct default_set {

	void operator () ( T& current, const T& val ) {
		current = val;
	}

	void operator () ( T& current, T&& val ) {
		current = std::move( val );
	}

};

template <typename T, 
    typename TGetter = default_get<T>, 
	typename TLValueSetter = default_set<T>, 
	typename TRValueSetter = default_set<T>>
	struct property
    : private std::tuple<TGetter, TLValueSetter, TRValueSetter> {
    private:
        using getset = std::tuple<TGetter, TLValueSetter, TRValueSetter>;
	public:
		T val;

		property ( const T& value, const TGetter& valuegetter = TGetter(), const TLValueSetter& lvaluesetter = TLValueSetter(), const TRValueSetter& rvaluesetter = TRValueSetter() )
		: getset( valuegetter, lvaluesetter, rvaluesetter ) {
			set( value );
		}

		T get () {
			return std::get<0>( *this )( val );
		}

		void set ( const T& right ) {
			std::get<1>( *this )( val, right );
		}

		void set ( T&& right ) {
			std::get<2>( *this )( val, std::forward<T>( right ) );
		}

		property& operator= ( const T& right ) {
			set( right );
			return *this;
		}
        
		property& operator= ( T&& right ) {
			set( std::move( right ) );
			return *this;
		}

		operator T () {
			return get();
		}
	};

int main ( int argc, char* argv[] ) {
    auto fget = []( int& v )->int { return v = 200; };
    property<int, decltype(fget)> prop( 500, fget );
    property<int> rawprop = 500;
    
    std::cout << prop << std::endl;
    std::cout << rawprop << std::endl;
    std::cout << sizeof(prop) << std::endl;
    std::cout << sizeof(rawprop) << std::endl;
}