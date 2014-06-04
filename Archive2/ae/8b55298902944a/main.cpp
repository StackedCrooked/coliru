#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>


#define PARAM_NAME param

#define PARAM(Index) BOOST_PP_CAT(PARAM_NAME, Index)

#define PARAM_DESCRIPTION(Index, Data, ParamType) \
    ParamType PARAM(BOOST_PP_SUB(Index, 2))

#define IS_BITWISE_SERIALIZABLE(TemplateClass, Params) \
template \
    < \
        BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(PARAM_DESCRIPTION,, Params)) \
    > \
struct is_bitwise_serializable \
    < \
        TemplateClass \
            < \
                BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Params), PARAM_NAME) \
            > \
    > \
    : boost::mpl::true_ {};


template <class T, class Enable>
struct MyClassA{};

template <class T>
struct MyClassB{};

template <int N>
struct MyClassC{};


template <class T>
struct is_bitwise_serializable : boost::mpl::false_{};

IS_BITWISE_SERIALIZABLE(MyClassA, (class)(class))

IS_BITWISE_SERIALIZABLE(MyClassB, (class))

IS_BITWISE_SERIALIZABLE(MyClassC, (int))


int main()
{
}