#include <type_traits>
#include <cassert>
#include <utility>
#include <new>

struct in_place_t {};
struct nullopt_t {};

const auto nullopt = nullopt_t();
const auto in_place = in_place_t();

template <typename T>
struct optional {
private:
	typedef typename std::aligned_storage<sizeof( T )>::type storage_type;
	bool present;
	storage_type storage;

	template <typename... Tn>
	void place( Tn&&... argn ) {
		assert( !present );
		new( std::addressof( storage ) ) T( std::forward<Tn>( argn )... );
		present = true;
	}

	void destroy( ) {
		assert( present );
		value( ).~T( );
		present = false;
	}

public:

	optional(  ) : optional( nullopt ) {

	}

	optional ( nullopt_t ) : present(false) {

	}

	template <typename ...Tn>
	explicit optional( in_place_t, Tn&&... argn ) : present(false) {
		place(std::forward<Tn>( argn )...);
	}

	optional ( const T& t ) : present(false) {
		place(t);
	}

	optional ( T&& t ) : present(false) {
		place(std::move(t));
	}

	optional(const optional& that) : present(false) {
		if ( std::addressof( that ) == this )
			return;
		if ( that.present )
			place(*that);
	}

	optional(optional&& that) : present(false) {
		if ( std::addressof( that ) == this )
			return;
		if ( that.present )
			place(std::move(*that));
	}

	optional& operator=(nullopt_t) {
		if ( present ) 
			destroy();
		return *this;
	}

	optional& operator=( T&& right ) {
		if ( present )
			destroy();
		place( std::move( right ) );
		return *this;
	}

	optional& operator=( const T& right ) {
		if ( present )
			destroy();
		place( right );
		return *this;
	}

	optional& operator=(const optional& that) {
		if ( std::addressof( that ) == this )
		    return *this;
		if ( present && that.present )
			**this = *that;
		else if ( present ) 
			destroy();
		else if(that.present) 
			place(*that);
		else 
			present = false;

		return *this;
	}

	optional& operator=(optional&& that) {
		if ( std::addressof( that ) == this )
			return;
		if ( present && that.present )
			value() = std::move( that.value() );
		else if ( present ) 
			destroy();
		else if ( that.present ) 
			place( std::move(*that) );
		else 
			present = false;

		return *this;
	}

	~optional() {
		if ( present ) 
			destroy();
	}

	T value_or ( T&& defaultvalue ) {
		if ( present )
			return value();
		return defaultvalue;
	}

	T& value() {
		return *static_cast<T*>( static_cast<void*>( std::addressof( storage ) ) );
	}

	const T& value() const {
		return *static_cast<T const*>( static_cast<void const*>( std::addressof( storage ) ) );
	}

	T& operator*() { 
		return value(); 
	}
	
	const T& operator*() const { 
		return value();
	}

	T* operator->( ) { 
		return std::addressof( value( ) ); 
	}
	
	const T* operator->( ) const { 
		return std::addressof( value( ) ); 
	}

	explicit operator bool() const { 
		return present; 
	}

};

template <typename T>
bool operator==( const optional<T>& left, const optional<T>& right ) {
	if ( left && right ) {
		return left.value( ) == right.value( );
	}
	else if ( !left && !right ) {
		return true;
	}
	return false;
}

template <typename T>
T maybe ( optional<T>& op, T&& defaultvalue ) {
	if ( op )
		return op.value();
	return defaultvalue;
}

template <typename T>
T maybe ( const optional<T>& op, T&& defaultvalue ) {
	if ( op )
		return op.value();
	return defaultvalue;
}

template <typename U, typename T, typename TFx>
T maybe ( optional<T>& op, U&& defaultvalue, TFx&& fx ) {
	if ( op )
		return fx( op.value() );
	return defaultvalue;
}

template <typename U, typename T, typename TFx>
U maybe ( const optional<T>& op, U&& defaultvalue, TFx&& fx ) {
	if ( op )
		return fx( op.value() );
	return defaultvalue;
}

int main () {
    optional<int> test1;
    optional<int> test2 = 1 + 1;
    optional<int> test3 = nullopt;
    optional<int> test4( in_place );
    optional<int> test5( nullopt );
    
    test1 = 1;
    test1 = nullopt;
    test1 = 2;
    test1 = test1;
}