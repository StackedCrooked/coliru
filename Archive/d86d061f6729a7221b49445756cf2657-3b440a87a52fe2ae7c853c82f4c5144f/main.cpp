#include <boost/preprocessor.hpp>
#define CLASSES ( 4, ( A, B, C, D ) )
#define FOWARD_CLASS( Z, N, _ ) class BOOST_PP_ARRAY_ELEM( N, CLASSES );

BOOST_PP_REPEAT( 4, FOWARD_CLASS, _ )
int main(){
    A *a{};(void)a;
    B *b{};(void)b;
    C *c{};(void)c;
    D *d{};(void)d;
}
