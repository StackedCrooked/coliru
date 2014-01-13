#include <boost/preprocessor.hpp>
void MARKER();

/***************************************************************************/

#define CONSTRUCT_CONCRETE_proc(name, tuple) /* макровызов обработки последовательности для proc-типов */ \
    myproc[name: tuple]

#define CONSTRUCT_CONCRETE_enum(name, tuple) /* макровызов обработки последовательности для enum-типов */ \
    myenum[name: BOOST_PP_TUPLE_REM() tuple]

#define CONSTRUCT_PROCS(unused, idx, seq) /* тут конкатинируем 'CONSTRUCT_CONCRETE_' и 'proc' или 'enum', и экспандим его */ \
    BOOST_PP_EXPAND(BOOST_PP_CAT(CONSTRUCT_CONCRETE_, BOOST_PP_SEQ_ELEM(idx, seq)))

#define CONSTRUCT(name, seq) \
    struct name { \
        BOOST_PP_REPEAT( \
             BOOST_PP_SEQ_SIZE(seq) \
            ,CONSTRUCT_PROCS \
            ,seq \
        ) \
    }; /* struct name */

/***************************************************************************/

CONSTRUCT(
    type1
    ,
    (proc(m0, (float)))
    (proc(m1, (int, long)))
    //(enum(mye1, (e0, e1, e2)))
)

/***************************************************************************/