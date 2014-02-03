#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <memory>

typedef std::size_t ulword;

template <ulword... I> 
struct indices { typedef indices type; };

template <ulword N, ulword... I>
struct make_indices : public make_indices<N - 1, N - 1, I...> { };

template <ulword... I>
struct make_indices<0, I...> : public indices<I...>{ };

namespace Furrovine {

    namespace detail {
		template <typename T, ulword i> 
		struct vector_member;
		
		template <typename T>
		struct vector_member<T, 0> {
			union { T x; T r; T s; };
		};

		template <typename T>
		struct vector_member<T, 1> {
			union { T y; T g; T t; };
		};

		template <typename T>
		struct vector_member<T, 2> {
			union { T z; T b; T u; };
		};

		template <typename T>
		struct vector_member<T, 3> {
			union { T w; T a; T v; };
		};

		template <typename T, typename TEat>
		struct vector_members;

		template <typename T, ulword... I>
		struct vector_members<T, indices<I...>> : public vector_member<T, I>... {};
	}

	template <typename T, ulword n>
	struct RVector : detail::vector_members<T, typename make_indices<n>::type> {
		typedef typename make_indices<n>::type indices_t;

		std::array<T, n>& cell( ) {
			return *static_cast<std::array<T, n>*>( static_cast<void*>( this ) );
		}

		const std::array<T, n>& cell( ) const {
			return *static_cast<const std::array<T, n>*>( static_cast<const void*>( this ) );
		}
		
		T* data( ) {
			return static_cast<T*>( static_cast<void*>( this ) );
		}

		const T* data( ) const {
			return static_cast<const T*>( static_cast<const void*>( this ) );
		}

		T& operator [] ( ulword i ) {
			return cell( )[ i ];
		}

		const static ulword size( ) {
			return n;
		}
	};

}

int main() {
    using namespace Furrovine;
    RVector<float, 3> arf;
    arf.x = 1.0f;
    arf.y = 2.0f;
	arf.z = 3.0f;
	
}
