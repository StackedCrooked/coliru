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
			T x;
		};

		template <typename T>
		struct vector_member<T, 1> {
			T y;
		};

		template <typename T>
		struct vector_member<T, 2> {
			T z;
		};

		template <typename T>
		struct vector_member<T, 3> {
			T w;
		};

		template <typename T, typename TEat>
		struct vector_members;

		template <typename T, ulword... I>
		struct vector_members<T, indices<I...>> : public vector_member<T, I>... {};
	}

	template <typename T, ulword n>
	struct RVector : public detail::vector_members<T, typename make_indices<n>::type> {
		typedef typename make_indices<n>::type indices_t;

    };

}

int main() {
    using namespace Furrovine;
    static_assert( std::is_pod<RVector<float, 3>>::value, "Fuck this shit." );
    static_assert( std::is_standard_layout<RVector<float, 3>>::value, "Fuck this shit." );
    static_assert( std::is_pod<detail::vector_member<float, 0>>::value, "Well, fuck!" );
    static_assert( std::is_pod<detail::vector_member<float, 1>>::value, "Well, fuck!" );
    static_assert( std::is_pod<detail::vector_member<float, 2>>::value, "Well, fuck!" );
    static_assert( std::is_pod<detail::vector_members<float, make_indices<3>::type>>::value, "Well, fuck!" );
}
