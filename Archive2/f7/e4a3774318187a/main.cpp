
#include <type_traits>
#include <utility>
#include <cassert>
#include <Furrovine++/in_place.h>
#include <Furrovine++/nullopt.h>
#include <Furrovine++/unqualified.h>
#include <Furrovine++/uninitialized.h>

namespace Furrovine {

    template <typename T>
	struct optional {
	private:
		bool present;
		uninitialized<T> storage;

		template <typename... Tn>
		void place( Tn&&... argn ) {
			assert( !present );
			unchecked_place( std::forward<Tn>( argn )... );
		}

		template <typename... Tn>
		void unchecked_place( Tn&&... argn ) {
			::new( std::addressof( storage ) ) T( std::forward<Tn>( argn )... );
			present = true;
		}

		void destroy( ) {
			assert( present );
			unchecked_destroy( );
		}

		void unchecked_destroy( ) {
			value( ).~T( );
			present = false;
		}

	public:

		optional( ) : optional( nullopt ) {

		}

		optional( nullopt_t ) : present( false ) {

		}

		template <typename ...Tn>
		explicit optional( in_place_t, Tn&&... argn ) {
			unchecked_place( std::forward<Tn>( argn )... );
		}

		optional( const T& t ) {
			unchecked_place( t );
		}

		optional( T&& t ) {
			unchecked_place( std::move( t ) );
		}

		optional( const optional& that ) : present( false ) {
			if ( that.present )
				place( *that );
		}

		optional( optional&& that ) : present( false ) {
			if ( that.present )
				place( std::move( *that ) );
		}

		optional& operator=( nullopt_t ) {
			if ( present )
				destroy( );
			return *this;
		}

		optional& operator=( T&& right ) {
			if ( present )
				destroy( );
			place( std::move( right ) );
			return *this;
		}

		optional& operator=( const T& right ) {
			if ( present )
				destroy( );
			place( right );
			return *this;
		}

		optional& operator=( const optional& that ) {
			if ( std::addressof( that ) == this )
				return *this;
			if ( present && that.present )
				**this = *that;
			else if ( present )
				destroy( );
			else if ( that.present )
				place( *that );
			else
				present = false;

			return *this;
		}

		optional& operator=( optional&& that ) {
			if ( std::addressof( that ) == this )
				return *this;
			if ( present && that.present )
				value( ) = std::move( that.value( ) );
			else if ( present )
				destroy( );
			else if ( that.present )
				place( std::move( *that ) );
			else
				present = false;

			return *this;
		}

		~optional( ) {
			if ( present )
				unchecked_destroy( );
		}

		T& value( ) {
			return *static_cast<T*>( static_cast<void*>( std::addressof( storage ) ) );
		}

		const T& value( ) const {
			return *static_cast<T const*>( static_cast<void const*>( std::addressof( storage ) ) );
		}

		T value_or( T defaultvalue ) {
			if ( present )
				return value( );
			return std::move( defaultvalue );
		}

		T value_or( T defaultvalue ) const {
			if ( present )
				return value( );
			return std::move( defaultvalue );
		}

		T& operator*( ) {
			return value( );
		}

		const T& operator*( ) const {
			return value( );
		}

		T* operator->( ) {
			return std::addressof( value( ) );
		}

		const T* operator->( ) const {
			return std::addressof( value( ) );
		}

		explicit operator bool( ) const {
			return present;
		}

	};

	template <typename T>
	struct optional<T&> {
	private:
		bool present;
		T& storage;

		template <typename... Tn>
		void place( Tn&&... argn ) {
			assert( !present );
			unchecked_place( std::forward<Tn>( argn )... );
		}

		template <typename... Tn>
		void unchecked_place( Tn&&... argn ) {
			present = true;
		}

		void destroy( ) {
			assert( present );
			unchecked_destroy( );
		}

		void unchecked_destroy( ) {
			present = false;
		}

	public:

		optional( ) : optional( nullopt ) {

		}

		optional( nullopt_t ) : present( false ), storage( null_ref<T>::value ) {

		}

		optional( T& t ) : present( true ), storage( t ) {
		
		}

		optional( const optional& that ) : present( that.present ), storage( that.present ? that.get( ) : null_ref<T>::value ) {
			
		}

		optional( optional&& that ) : present( that.present ), storage( that.present ? that.get( ) : null_ref<T>::value ) {
			if ( that.present )
				that.unchecked_destroy( );
		}

		optional& operator=( nullopt_t ) {
			if ( present )
				unchecked_destroy( );
			return *this;
		}

		~optional( ) {
			if ( present )
				unchecked_destroy( );
		}

		T& value( ) {
			return storage;
		}

		const T& value( ) const {
			return storage;
		}

		T value_or( T defaultvalue ) {
			if ( present )
				return value( );
			return std::move( defaultvalue );
		}

		T value_or( T defaultvalue ) const {
			if ( present )
				return value( );
			return std::move( defaultvalue );
		}

		T& operator*( ) {
			return value( );
		}

		const T& operator*( ) const {
			return value( );
		}

		explicit operator bool( ) const {
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

	namespace detail {
		struct pass {
			template <typename T>
			auto operator()( T&& x ) -> decltype( x ) {
				return x;
			}
		};

		struct gen {
			template <typename T>
			T operator() ( ) {
				return T( );
			}
		};
	}

	template <typename T, typename TFx, typename TGx>
	T maybe( optional<T>& op, TFx&& fx, TGx&& defaultgen ) {
		if ( op )
			return fx( op.value( ) );
		return defaultgen( );
	}

	template <typename T, typename TFx, typename TGx>
	T maybe( const optional<T>& op, TFx&& fx, TGx&& defaultgen ) {
		if ( op )
			return fx( op.value( ) );
		return defaultgen( );
	}

	template <typename T, typename TFx>
	T maybe( optional<T>& op, TFx&& fx ) {
		return maybe( op,
			std::forward<TFx>( fx ),
			detail::gen( ) );
	}

	template <typename T, typename TFx>
	T maybe( const optional<T>& op, TFx&& fx ) {
		return maybe( op,
			std::forward<TFx>( fx ),
			detail::gen( ) );
	}

	template <typename T>
	T maybe( optional<T>& op ) {
		return maybe( op,
			detail::pass( ),
			detail::gen( ) );
	}

	template <typename T>
	T maybe( const optional<T>& op ) {
		return maybe( op,
			detail::pass( ),
			detail::gen( ) );
	}

	template <typename T, typename U>
	T maybe_or( optional<T>& op, U&& defaultvalue ) {
		typedef typename unqualified<decltype( defaultvalue )>::type return_t;
		return maybe( op,
			detail::pass( ),
			[ defaultvalue ] ( ) -> return_t { return defaultvalue; } );
	}

	template <typename T, typename U>
	T maybe_or( const optional<T>& op, U&& defaultvalue ) {
		typedef typename unqualified<decltype( defaultvalue )>::type return_t;
		return maybe( op,
			detail::pass( ),
			[ defaultvalue ] ( ) -> return_t { return defaultvalue; } );
	}

	template <typename T, typename TGx, typename TFx>
	T maybe_gen( optional<T>& op, TGx&& defaultgen, TFx&& fx ) {
		maybe( op, fx, defaultgen );
	}

	template <typename T, typename TGx, typename TFx>
	T maybe_gen( const optional<T>& op, TGx&& defaultgen, TFx&& fx ) {
		maybe( op, fx, defaultgen );
	}

	template <typename T, typename TGx>
	T maybe_gen( optional<T>& op, TGx&& defaultgen ) {
		return maybe( op,
			detail::pass(),
			std::forward<TGx>( defaultgen ) );
	}

	template <typename T, typename TGx>
	T maybe_gen( const optional<T>& op, TGx&& defaultgen ) {
		return maybe( op,
			detail::pass(),
			std::forward<TGx>( defaultgen ) );
	}

	template <typename T>
	T maybe_gen( optional<T>& op ) {
		return maybe( op,
			detail::pass(),
			detail::gen() );
	}

	template <typename T>
	T maybe_gen( const optional<T>& op ) {
		return maybe( op,
			detail::pass(),
			detail::gen() );
	}

}

int main () {
    
    // *Sniff* Goodbyte, awesome syntax. I hardly knew ye. ;(
    //float f = pi<float>;
    float f = pi<float>();
}

