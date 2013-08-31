#include <boost/preprocessor.hpp>

#define GET_COMMA() ,
#define GET_NOTHING()

#define GET_TUPLE_HEAD_TYPE(Fields) \
    BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_HEAD(Fields))
    

#define GET_TUPLE_TAIL_TYPES(r, sep, Field) \
    , BOOST_PP_SEQ_HEAD(Field)
    
    
#define GET_FIELD_TYPE(Field) \
    BOOST_PP_SEQ_HEAD(Field)
    
#define GET_FIELD_TYPE_(r, Sep, Field) \
    Sep() BOOST_PP_SEQ_HEAD(Field)

#define GET_FIELD_TYPES(Fields) \
    BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_HEAD(Fields)) \
    BOOST_PP_SEQ_FOR_EACH(GET_FIELD_TYPE_, GET_COMMA, BOOST_PP_SEQ_TAIL(Fields))

#define GET_TUPLE(Fields) std::tuple< GET_FIELD_TYPES(Fields) >
    
#define GET_FIELD_NAME(Field) \
    BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(Field))
    
#define GET_FIELD_NAME_(r, sep, Field) \
    sep() BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(Field))
    
#define GET_FIELD_NAMES(Fields) \
    BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(BOOST_PP_SEQ_HEAD(Fields))) \
    BOOST_PP_SEQ_FOR_EACH(GET_FIELD_NAME_, GET_COMMA, BOOST_PP_SEQ_TAIL(Fields))

#define GET_FIELD_ACCESSOR(r, sep, Field) \
    GET_FIELD_TYPE(Field) & GET_FIELD_NAME(Field);

#define GET_FIELD_ACCESSORS(Fields) \
    BOOST_PP_SEQ_FOR_EACH(GET_FIELD_ACCESSOR, _, Fields)

#define GET_SEPARATOR0()
#define GET_SEPARATOR1() ,
#define GET_SEPARATOR2() ,
#define GET_SEPARATOR3() ,
#define GET_SEPARATOR4() ,
#define GET_SEPARATOR6() ,
#define GET_SEPARATOR7() ,
#define GET_SEPARATOR8() ,
#define GET_SEPARATOR9() ,
#define GET_SEPARATOR10() ,

#define GET_FIELD_INITIALIZER(r, sep, i, Field) \
    BOOST_PP_CAT(GET_SEPARATOR, i)() GET_FIELD_NAME(Field)( std::get<i>(*this))
    
#define GET_FIELD_INITIALIZERS(Fields) \
    BOOST_PP_SEQ_FOR_EACH_I(GET_FIELD_INITIALIZER, GET_COMMA, Fields)

#define GET_MESSAGE(Name, Fields) \
    struct Name : GET_TUPLE(Fields) { \
        Name() : GET_TUPLE(Fields)(GET_FIELD_NAMES(Fields)) , \
                 GET_FIELD_INITIALIZERS(Fields) { \
        }; \
        GET_FIELD_ACCESSORS(Fields) \
    };



GET_MESSAGE(Point, ((int)(x))((int)(y))((int)(z)))


    