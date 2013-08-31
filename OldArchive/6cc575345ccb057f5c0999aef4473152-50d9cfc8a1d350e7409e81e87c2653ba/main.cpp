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
	typename TRValueSetter = TLValueSetter, 
	bool isdefaultconstructible = 
	std::is_default_constructible<TGetter>::value && 
	std::is_default_constructible<TLValueSetter>::value && 
	std::is_default_constructible<TRValueSetter>::value>
struct property;

template <typename T, 
	typename TGetter, 
	typename TLValueSetter, 
	typename TRValueSetter>
struct property<T, TGetter, TLValueSetter, TRValueSetter, true> {
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

template <typename T, 
	typename TGetter, 
	typename TLValueSetter, 
	typename TRValueSetter>
struct property<T, TGetter, TLValueSetter, TRValueSetter, false> {
public:
	TGetter getter;
	TLValueSetter lsetter;
	TRValueSetter rsetter;
	T val;

    property ( const TGetter& valuegetter, const TLValueSetter& lvaluesetter = TLValueSetter(), const TRValueSetter& rvaluesetter = TRValueSetter() )
	: getter( valuegetter ), lsetter( lvaluesetter ), rsetter( rvaluesetter ) {

	}

	property ( const T& value, const TGetter& valuegetter, const TLValueSetter& lvaluesetter = TLValueSetter(), const TRValueSetter& rvaluesetter = TRValueSetter() )
	: getter( valuegetter ), lsetter( lvaluesetter ), rsetter( rvaluesetter ) {
		set( value );
	}

	property ( T&& value, const TGetter& valuegetter, const TLValueSetter& lvaluesetter, const TRValueSetter& rvaluesetter )
	: getter( valuegetter ), lsetter( lvaluesetter ), rsetter( rvaluesetter ) {
		set( std::forward<T>( value ) );
	}

	T get () {
		return getter( val );
	}

	void set ( const T& right ) {
		lsetter( val, right );
	}

	void set ( T&& right ) {
		rsetter( val, std::forward<T>( right ) );
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
    auto fget = []( int& v )->int { return v = 200; };
    property<int, decltype(fget)> prop( 500, fget );
    property<int> rawprop = 500;
    
    std::cout << prop << std::endl;
    std::cout << rawprop << std::endl;
    std::cout << sizeof(prop) << std::endl;
    std::cout << sizeof(rawprop) << std::endl;
}