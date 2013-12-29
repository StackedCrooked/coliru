#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>


#define GEN_MACRO_0(X, Y)                             \
    ((X, Y)) GEN_MACRO_1
#define GEN_MACRO_1(X, Y)                             \
    ((X, Y)) GEN_MACRO_0
#define GEN_MACRO_0_END
#define GEN_MACRO_1_END

#define SHOW(name,val)                               \
        std::cout << name << " : " << val ;

#define SHOW_TUPLE(r,_,tupple)                       \
       SHOW("1st",BOOST_PP_TUPLE_ELEM(2,0,tupple))   \
       SHOW("\t2nd",BOOST_PP_TUPLE_ELEM(2,1,tupple)) \
       std::cout << std::endl;
#define OUTPUT (ADD_PAREN_1 INPUT,_END) 


#define SHOW_NODES(seq)                              \
        BOOST_PP_SEQ_FOR_EACH(SHOW_TUPLE,_,          \
                 BOOST_PP_CAT(GEN_MACRO_0 seq,_END) )

int main() {
    SHOW_NODES(
        ("cock","unskill")
        ("rock","hard")
        ("price","over 100500")
        )
}