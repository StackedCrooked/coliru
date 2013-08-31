#include <utility>
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
		current = val;
	}

};


template <typename T, typename TGetter = default_get<T>, typename TLValueSetter = default_set<T>, typename TRValueSetter = TLValueSetter>
struct property {
public:
	T val;

	property () {

	}

	property ( const T& value ) {
		set( value );
	}

	property ( T&& value ) {
		set( std::forward<T>( value ) );
	}
    
    T get () {
        TGetter getter;
    	return getter( val );
    }
    
    void set ( const T& right ) {
        TLValueSetter setter;
    	setter( val, right );
    }
    
    void set ( T&& right ) {
        TRValueSetter setter;
    	setter( val, std::forward<T>( right ) );
    }

	property& operator= ( const T& right ) {
		set( right );
		return *this;
	}

	property& operator= ( T&& right ) {
		set( std::forward<T>( right ) );
        return *this;
	}

	operator T () {
		return get();
	}
};

int main ( int argc, char* argv[] ) {
    
    property<int> props = 200;
    std::cout << props << std::endl;
}