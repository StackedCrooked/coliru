#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/cat.hpp>

template<template<typename> class Monad>
struct MonadUnit
{
    template<typename T> auto operator()(T x) const
    {
        return Monad<T>{x};
    }
};

#define SEQ_LAST(SEQ) BOOST_PP_SEQ_ELEM( BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(SEQ)), SEQ)

#define STMT_TAIL(r, data, elem) };

#define LAST_STMT(var, code) unit( var );

#define STMT_HEAD_AUX(var, code) code >>= [=](auto var) { return
#define STMT_HEAD(r, data, elem) STMT_HEAD_AUX elem

#define DO_AUX(SEQ) \
    BOOST_PP_SEQ_FOR_EACH(STMT_HEAD, _, SEQ) \
    BOOST_PP_EXPAND(LAST_STMT SEQ_LAST(SEQ)) \
    BOOST_PP_SEQ_FOR_EACH(STMT_TAIL, _, SEQ) \
/**/

#define DO(MONAD, SEQ) \
    ([=] \
    { \
        const auto unit = MonadUnit<MONAD>{}; \
        return \
    DO_AUX( BOOST_PP_SEQ_TAIL(BOOST_PP_CAT(BOOST_FUSION_ADAPT_STRUCT_FILLER_0(0,0)SEQ, _END)) ) \
    })() \
/**/

/******************************************************************************/

#include <boost/optional.hpp>

#include <iostream>
#include <utility>
#include <cassert>

using namespace std;
using namespace boost;

// Simple Monad:
template<typename T>
struct Simple
{
    T data;
    template<typename F> friend auto operator>>=(Simple m, F f)
    {
        return f(m.data);
    }
};

// Maybe Monad:
template<typename F, typename T>
auto operator>>=(optional<T> m, F f)
{
    return m ? f(m.get()) : m;
}

template<template<typename> class Monad>
auto run()
{
    return
        DO(Monad,
            (x, unit(1))
            (y, unit(2))
            (z, DO(Monad,
                (x, unit(5))
                (_, unit(x - 2))
            ))
            (_, unit(x + y + z))
        );
}

int main()
{
    assert( run<Simple>().data == 6 );
    assert( run<optional>().get() == 6 );
    assert
    (
        not DO(optional,
            (x, unit(1))
            (y, unit(2))
            (z, DO(optional,
                (x, make_optional(false, 5))
                (_, unit(x - 2))
            ))
            (_, unit(x + y + z))
        )
    );
    cout << "DONE" << endl;
}
