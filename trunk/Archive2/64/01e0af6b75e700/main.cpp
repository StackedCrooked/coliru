#include <iostream>
#include <boost/preprocessor.hpp>

#define X_ERR_OK (0)
#define X_ERR_FOO (816)
#define X_ERR_OTHER (842)


#define XX_ERR_CASE( r, _, e ) case BOOST_PP_TUPLE_ELEM(2,0,e): return BOOST_PP_TUPLE_ELEM(2,1,e);
#define XX_ERRORS( seq ) \
    const char* err_name2( int err ) { \
        switch( err ) { \
        BOOST_PP_SEQ_FOR_EACH( XX_ERR_CASE, _, seq ) \
        } \
        return "<unknown>";  }
        
#define E(M) ((M, #M))

XX_ERRORS(
    E(X_ERR_OK)
    E(X_ERR_FOO)
    E(X_ERR_OTHER)
)

int main()
{
    std::cout << err_name2(816) << std::endl;
}