#include <boost/preprocessor.hpp>

//Heavily "inspired" from BOOST_FUSION_ADAPT_STRUCT
#define FIX_EVENT_SEQUENCE_FILLER_0(X, Y)  \
    ((X, Y)) FIX_EVENT_SEQUENCE_FILLER_1
#define FIX_EVENT_SEQUENCE_FILLER_1(X, Y)  \
    ((X, Y)) FIX_EVENT_SEQUENCE_FILLER_0
#define FIX_EVENT_SEQUENCE_FILLER_0_END
#define FIX_EVENT_SEQUENCE_FILLER_1_END


#define GET_EVENT_NAME(NAME_AND_SIG) \
BOOST_PP_TUPLE_ELEM(2,0,NAME_AND_SIG)

#define GET_EVENT_SIG(NAME_AND_SIG) \
BOOST_PP_TUPLE_ELEM(2,1,NAME_AND_SIG)

#define GET_NTH(N,EVENTS) \
BOOST_PP_SEQ_ELEM(N,EVENTS)

#define DECLARE_EVENT_NAME(R,_,NAME_AND_SIG) \
struct GET_EVENT_NAME(NAME_AND_SIG);

#define FIX_EVENT_SEQUENCE(EVENTS) \
BOOST_PP_CAT( FIX_EVENT_SEQUENCE_FILLER_0 EVENTS, _END )

#define DECLARE_EVENT_NAMES(EVENTS) \
BOOST_PP_SEQ_FOR_EACH(DECLARE_EVENT_NAME, _, EVENTS )

#define CREATE_FUSION_PAIR(R,N,EVENTS) \
boost::fusion::pair<GET_EVENT_NAME(GET_NTH(N,EVENTS)),boost::signals2::signal<GET_EVENT_SIG(GET_NTH(N,EVENTS))> >

#define ENUM_EVENT_PAIRS(EVENTS) \
BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(EVENTS), CREATE_FUSION_PAIR, EVENTS )

#define CONSTRUCT_EVENTS(NAME,EVENTS) \
template <> struct EventTraits<NAME>  \
{                                     \
DECLARE_EVENT_NAMES(FIX_EVENT_SEQUENCE(EVENTS))           \
typedef boost::fusion::map<           \
ENUM_EVENT_PAIRS(FIX_EVENT_SEQUENCE(EVENTS))              \
> Events;                             \
};



template <typename T> struct EventTraits;

class SomeClass;


CONSTRUCT_EVENTS(
    SomeClass,
    (Started, void())
    (Finished, void(int))
)





