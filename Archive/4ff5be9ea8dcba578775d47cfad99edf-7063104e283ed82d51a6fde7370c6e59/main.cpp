#include <iostream>
#include <tuple>
#include <utility>
#include <type_traits>
#include <functional>
#include <vector>
#include <cassert>

struct none_t {};
const auto none = none_t{};

template <typename T>
    struct optional {
	public:

		optional ( none_t ) : present(false) {

		}

		template <typename ...Tn>
		explicit optional ( Tn&&... argn ) : present(false) {
			if ( sizeof...( argn ) > 0 )
				place(std::forward<Tn>( argn )...);
		}

		optional ( const T& t ) : present(false) {
			place(t);
		}

		optional ( T&& t ) : present(false) {
			place(std::move(t));
		}

		optional(const optional& that) : present(false) {
			if ( that.present ) 
				place(*that);
			else 
				present = false;
		}

		optional(optional&& that) : present(false) {
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

		T get_or ( T&& defaultvalue ) {
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

	template <typename T>
	T maybe ( optional<T>& op, T&& defaultvalue ) {
		if ( op )
			return op.get();
		return defaultvalue;
	}

	template <typename T>
	T maybe ( const optional<T>& op, T&& defaultvalue ) {
		if ( op )
			return op.get();
		return defaultvalue;
	}

	template <typename U, typename T, typename TFx>
	T maybe ( optional<T>& op, U&& defaultvalue, TFx&& fx ) {
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

struct tribool {
private:
    optional<bool> tri;
public:

    tribool () {
        
    }
    
    tribool ( none_t ) : tri( none ) {
        
    }
    
    tribool ( bool value ) : tri( value ) {
        
    }
    
    tribool ( const tribool& copy ) : tri( copy ) {
        
    }
    
    tribool ( tribool&& mov ) : tri( std::move( mov ) ) {
        
    }

    explicit operator bool () const {
        return tri && tri.get();
    }

    bool operator! () const {
        return tri ? !tri.get() : false;
    }
    
    tribool& operator= ( bool value ) {
        tri = value;
        return *this;
    }
    
    tribool& operator= ( const none_t& ) {
        tri = none;
        return *this;
    }
    
    tribool& operator= ( const tribool& copy ) {
        tri = copy.tri;
        return *this;
    }
    
    tribool& operator= ( tribool&& value ) {
        tri = std::move( value.tri );
        return *this;
    }
};

void State ( const tribool& b ) {
    if ( b ) {
        std::cout << "True" << std::endl;
    }
    else if ( !b ) {
        std::cout << "False" << std::endl;
    }
    else {
        std::cout << "Indeterminate" << std::endl;
    }
}

int main ( int argc, char** argv ) {
    
    tribool b;
    
    std::cout << "b = true: ";
    b = true;
    State( b );
    
    std::cout << "b = false: ";
    b = false;
    State( b );
    
    std::cout << "b = none: ";
    b = none;
    State( b );
    
}