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
        template <typename T, ulword skew>
		struct back_stack {
            // SO EMPTY IT HURTS
            /*operator T& () {
                return *( static_cast<T*>( static_cast<void*>( this ) ) - skew );
            }
            
            operator const T& () const {
                return *( static_cast<const T*>( static_cast<const void*>( this ) ) - skew );
            }*/
            
            //T& operator= ( const T& value ) {
             //   T& item = *this;
             //   item = value;
             //   return *this;
            //}
        };
        
        template <typename T, ulword i, ulword n>
		struct vector_member;

		template <typename T, ulword n>
		struct vector_member<T, 0, n> : public back_stack<T, n> {
		
        };

		template <typename T, ulword n>
		struct vector_member<T, 1, n> : public back_stack<T, n - 1> {
		
        };

		template <typename T, ulword n>
		struct vector_member<T, 2, n> : public back_stack<T, n - 2> {
		
        };

		template <typename T, ulword n>
		struct vector_member<T, 3, n> : public back_stack<T, n - 3> {
		
        };

		template <typename T, ulword n, typename TEat>
		struct vector_members;

		template <typename T, ulword n, ulword... I>
		struct vector_members<T, n, indices<I...>> : public vector_member<T, I, n>... {};
	}

	template <typename T, ulword n>
	struct RVector {
		typedef typename make_indices<n>::type indices_t;
        
        std::array<T, n> _res;
        
        
    };
    
    template <typename T>
    struct RVector2 {
        detail::back_stack<T, 2> x;
        detail::back_stack<T, 1> y;
    };

}

int main() {
    using namespace Furrovine;
    static_assert( std::is_pod<RVector<float, 3>>::value, "Fuck this shit." );
    static_assert( std::is_standard_layout<RVector<float, 3>>::value, "Fuck this shit." );
    static_assert( std::is_pod<detail::vector_member<float, 0, 3>>::value, "Well, fuck!" );
    static_assert( std::is_pod<detail::vector_member<float, 1, 3>>::value, "Well, fuck!" );
    static_assert( std::is_pod<detail::vector_member<float, 2, 3>>::value, "Well, fuck!" );
    static_assert( std::is_pod<detail::vector_members<float, 3, make_indices<3>::type>>::value, "Well, fuck!" );

    //static_assert( std::is_pod<RVector2<float>>::value, "Damnit ._." );
    //static_assert( std::is_standard_layout<RVector2<float>>::value, "Damnit ._." );
    //static_assert( sizeof( RVector2<float> ) == 8, "Even more damnit!" );
    std::cout << sizeof( RVector2<float> );
    //RVector2<float> meow;
    //meow.x = 2.56f;
    //meow.y = 3.78f;
    //std::cout << meow.x << " " << meow.y << std::endl;
}
