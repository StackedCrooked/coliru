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
    
    

#define GET_SEPARATOR(NUM) ,

#define GET_CONSTRUCTOR_ARG_(r, sep, Field) \
    , const GET_FIELD_TYPE(Field) & BOOST_PP_CAT(in, GET_FIELD_NAME(Field))

#define GET_CONSTRUCTOR_ARGS(Fields) \
    const GET_FIELD_TYPE(BOOST_PP_SEQ_HEAD(Fields)) & BOOST_PP_CAT(in, GET_FIELD_NAME(BOOST_PP_SEQ_HEAD(Fields))) \
    BOOST_PP_SEQ_FOR_EACH(GET_CONSTRUCTOR_ARG_, _, BOOST_PP_SEQ_TAIL(Fields))
    
#define GET_FIELD_INITIALIZER_(r, sep, i, Field) \
    , GET_FIELD_NAME(Field)( std::get<i>(*this))
    
#define GET_FIELD_INITIALIZERS(Fields) \
    const BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_HEAD(Fields)) & BOOST_PP_CAT(in, GET_FIELD_NAME(BOOST_PP_SEQ_HEAD(Fields))) \
    BOOST_PP_SEQ_FOR_EACH_I(GET_FIELD_INITIALIZER_, GET_COMMA, BOOST_PP_SEQ_TAIL(Fields))

#define GENERATE_MESSAGE(Name, Fields) \
    struct Name : GET_TUPLE(Fields) ;{ \
        Name(GET_CONSTRUCTOR_ARGS(Fields)) ; GET_TUPLE(Fields)(GET_FIELD_NAMES(Fields)) , \
                 GET_FIELD_INITIALIZERS(Fields) { \
        }; \
        GET_FIELD_ACCESSORS(Fields) \
    };



GENERATE_MESSAGE(Point, ((int)(x))((int)(y))((int)(z)))

GENERATE_MESSAGE(InterfaceDescriptor, ((std::string)(InterfaceType))((std::string)(LinkStatus))((int32_t)(PortCount))((std::string)(MACAddress))((std::string)(VendorName))((std::string)(ProductName)))


    