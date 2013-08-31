#include <boost/preprocessor.hpp>

#define HEAD BOOST_PP_SEQ_HEAD
#define TAIL BOOST_PP_SEQ_TAIL
#define EACH BOOST_PP_SEQ_FOR_EACH 
#define ELEM BOOST_PP_SEQ_ELEM
#define FIRST(Seq) ELEM(0, Seq)
#define SECOND(Seq) ELEM(1, Seq)

#define GENERATE_COMMA() ,
#define GENERATE_SEMICOLON() ;
#define GENERATE_NOTHING()

#define FIRST_(r, GenSep, Pair) GenSep() FIRST(Pair)
#define SECOND_(r, GenSep, Pair) GenSep() SECOND(Pair)


#define MAP_FIRST(Fields, GenSep) \
    FIRST(HEAD(Fields)) EACH(FIRST_, GenSep, TAIL(Fields))

#define MAP_SECOND(Fields, GenSep) \
    SECOND(HEAD(Fields)) EACH(SECOND_, GenSep, TAIL(Fields))
    
    
#define SEQ ((int)(x))((char)(y))((float)(z))

MAP_FIRST(SEQ, GENERATE_SEMICOLON)
MAP_SECOND(SEQ, GENERATE_SEMICOLON)

