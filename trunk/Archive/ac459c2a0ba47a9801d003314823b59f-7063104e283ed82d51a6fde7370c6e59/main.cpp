#include <type_traits>
#include <utility>
#include <cassert>
#include <memory>
#include <iostream>

struct none_t {};

const auto none = none_t ();

template <typename T>
    struct optional {
	public:

		optional ( none_t ) : present(false) {

		}

		template <typename ...Tn>
		explicit optional ( Tn&&... argn ) : present(false) {
			place(std::forward<Tn>( argn )...);
		}

		optional () : present(false) {

		}

		optional ( const T& t ) : present(false) {
			place(t);
		}

		optional ( T&& t ) : present(false) {
			place(std::move(t));
		}

		optional(const optional& that) {
			if ( that.present ) 
				place(*that);
			else 
				present = false;
		}

		optional(optional&& that) {
			if ( that.present ) 
				place(std::move(*that));
			else 
				present = false;
		}

		optional& operator=(none_t) {
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
			if ( present && that.present ) 
				**this = std::move(*that);
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

		template <typename U>
		U get_or ( U&& defaultvalue ) {
			if ( present )
				return get();
			return defaultvalue;
		}

		T& get() {
			return *static_cast<T*>(static_cast<void*>(&storage));
		}

		const T& get() const {
			return *static_cast<T const*>(static_cast<void const*>(&storage));
		}

		T& operator*() { return get(); }
		const T& operator*() const { return get(); }

		T* operator->() { return &get(); }
		const T* operator->() const { return &get(); }

		explicit operator bool() const { return present; }

	private:
		typedef typename std::aligned_storage<sizeof( T )>::type storage_type;

		template <typename... Tn>
		void place(Tn&&... argn) {
			assert(!present);
			::new( &storage ) T( std::forward<Tn>( argn )... );
			present = true;
		}

		void destroy () {
			assert(present);
			get().~T();
			present = false;
		}

		bool present;
		storage_type storage;
	};

	template <typename U, typename T>
	U maybe ( optional<T>& op, U&& defaultvalue ) {
		if ( op )
			return op.get();
		return defaultvalue;
	}

	template <typename U, typename T>
	U maybe ( const optional<T>& op, U&& defaultvalue ) {
		if ( op )
			return op.get();
		return defaultvalue;
	}

	template <typename U, typename T, typename TFx>
	U maybe ( optional<T>& op, U&& defaultvalue, TFx&& fx ) {
		if ( op )
			return fx( op.get() );
		return defaultvalue;
	}

	template <typename U, typename T, typename TFx>
	U maybe ( const optional<T>& op, U&& defaultvalue, TFx&& fx ) {
		if ( op )
			return fx( op.get() );
		return defaultvalue;
	}


int main () {
    std::cout << std::hex;
    
    optional<int> op;
    std::cout << op.get_or( 0xC1CADA ) << std::endl;
	op = 24;
	std::cout << op.get_or( 0xC1CADA ) << std::endl;
	op = none;
	std::cout << op.get_or( 0xC1CADA ) << std::endl;
    
}