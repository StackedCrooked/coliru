#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define GET_TUPLE_HEAD_TYPE(Fields) \
    BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_HEAD(Fields))
    

#define GET_TUPLE_TAIL_TYPES(r, sep, Field) \
    , BOOST_PP_SEQ_HEAD(Field)


#define GET_TUPLE(Fields) \
    std::tuple< GET_TUPLE_HEAD_TYPE(Fields) \
                BOOST_PP_SEQ_FOR_EACH(GET_TUPLE_TAIL_TYPES, _, BOOST_PP_SEQ_TAIL(Fields)) >

#define GET_FIELD_TYPE(Field) \
    BOOST_PP_SEQ_HEAD(Field)
    
#define GET_FIELD_NAME(Field) \
    BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(Field))

#define GET_FIELD_ACCESSOR(r, sep, Field) \
    GET_FIELD_TYPE(Field) & GET_FIELD_NAME(Field);

#define GET_FIELD_ACCESSORS(Fields) \
    BOOST_PP_SEQ_FOR_EACH(GET_FIELD_ACCESSOR, _, Fields)

#define GET_COMMA() ,
#define GET_NOTHING()

#define GET_FIELD_INITIALIZER(r, sep, Field) \
    sep() GET_FIELD_NAME(Field)(GET_FIELD_NAME(Field))
    
#define GET_FIELD_INITIALIZERS(Fields) \
    GET_FIELD_INITIALIZER(_, GET_NOTHING, BOOST_PP_SEQ_HEAD(Fields)) \
    BOOST_PP_SEQ_FOR_EACH(GET_FIELD_INITIALIZER, GET_COMMA, BOOST_PP_SEQ_TAIL(Fields))

#define GET_MESSAGE(Name, Fields) \
    struct Name : GET_TUPLE(Fields) { \
        Name() : GET_FIELD_INITIALIZERS(Fields) {} \
        GET_FIELD_ACCESSORS(Fields) \
    };


GET_MESSAGE(Point, ((int)(x))((int)(y))((int)(z)))

    