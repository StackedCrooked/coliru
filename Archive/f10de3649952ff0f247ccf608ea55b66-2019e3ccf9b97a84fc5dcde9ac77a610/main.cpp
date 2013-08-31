#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define GET_TUPLE_HEAD_TYPE(Fields) \
    BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_HEAD(Fields))
    

#define GET_TUPLE_TAIL_TYPES(_, GetSeparator, Field) \
    , BOOST_PP_SEQ_HEAD(Field)


#define GET_TUPLE(Fields) \
    std::tuple< GET_TUPLE_HEAD_TYPE(Fields) \
                BOOST_PP_SEQ_FOR_EACH(GET_TUPLE_TAIL_TYPES, _, BOOST_PP_SEQ_TAIL(Fields)) >


#define GET_MESSAGE(Fields) \
    GET_TUPLE(Fields)


GET_MESSAGE(((int)(x))((int)(y))((int)(z)))


    