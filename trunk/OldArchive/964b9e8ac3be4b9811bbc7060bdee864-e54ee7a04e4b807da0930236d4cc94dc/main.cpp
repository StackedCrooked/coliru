#include <stdint.h>

// CPPX_NOT_USING( a )
// * Suppresses unused warning about `a` out the enclosing scope.
// * In `CPPX_NOT_USING( a ) statement;`, compilation error if `a` is used in statement.
// * Compilation error if `a` does not exist.
// * Can be nested, e.g. like `CPPX_NOT_USING( a ) CPPX_NOT_USING( b ) statement;`.
// * Employs several quite dubious constructs. :-)

#if defined( CPPX_NOT_USING )
    #undef CPPX_NOT_USING
    #define CPPX_NOT_USING( a )
#else
    #define CPPX_NOT_USING( a ) \
    for( \
        struct a##__is_declared_unused \
            **cppx_once_loop_variable = ( \
                ::cppx::intentionally_unused( a ), \
                reinterpret_cast<a##__is_declared_unused**>( \
                    &::cppx::detail::A_valid_location::somewhere \
                    ) \
                ), \
            &a = *reinterpret_cast<a##__is_declared_unused*>( \
                &::cppx::detail::A_valid_location::somewhere \
                ); \
        !!cppx_once_loop_variable; \
        (::cppx::intentionally_unused( a ), cppx_once_loop_variable = 0) \
        )
#endif

namespace cppx {
    namespace detail {
        template< class Dummy >
        struct A_valid_location_
        {
            static intptr_t somewhere;
        };

        template< class Dummy >
        intptr_t A_valid_location_<Dummy>::somewhere;

        typedef A_valid_location_<void> A_valid_location;
    }

    template< class Arguments >
    void intentionally_unused( Arguments const& ) {}
}  // namespace cppx

#include <iostream>
using namespace std;
int main( int argc, char* argv[] )
{
    CPPX_NOT_USING( argv )
    {
        cout << argc << " arguments." << endl;
    }
}
