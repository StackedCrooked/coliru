#include <boost/preprocessor/repetition/repeat.hpp>
#define GET_STR_AUX(_, i, str) (sizeof(str) > (i) ? str[(i)] : 0),
#define GET_STR(str) BOOST_PP_REPEAT(64,GET_STR_AUX,str) 0

template<char...> struct sequence;


template<typename T>
void type_is();

int main()
{
    type_is<sequence<GET_STR("Hello world!")>>();
}
