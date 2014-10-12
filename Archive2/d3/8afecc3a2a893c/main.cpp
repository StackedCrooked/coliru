// Copyright Evgeny Panasyuk 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// e-mail: E?????[dot]P???????[at]gmail.???

// Emulation of "Anonymous Types"

// GOTO main

#include <boost/preprocessor/seq/pop_front.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <iostream>
#include <utility>

using namespace std;
using namespace boost;
using namespace fusion;

// refer http://www.boost.org/doc/libs/1_56_0/boost/fusion/adapted/struct/define_struct.hpp
#define ANONYMOUS_TYPE_0(X, Y) ((X, Y)) ANONYMOUS_TYPE_1
#define ANONYMOUS_TYPE_1(X, Y) ((X, Y)) ANONYMOUS_TYPE_0
#define ANONYMOUS_TYPE_0_END
#define ANONYMOUS_TYPE_1_END

#define VAR_NAME(elem) BOOST_PP_TUPLE_ELEM(2, 0, elem)
#define VAR_VALUE(elem) BOOST_PP_TUPLE_ELEM(2, 1, elem)
#define MOVE_VAR(r, data, elem) std::move(BOOST_PP_CAT(VAR_NAME(elem), __aux)),
#define DECLARE_VAR(r, data, elem) auto BOOST_PP_CAT(VAR_NAME(elem), __aux) = VAR_VALUE(elem);
#define DECLARE_MEMBER(r, data, elem) decltype(BOOST_PP_CAT(VAR_NAME(elem), __aux)) VAR_NAME(elem);

#define FOR_EACH_DECL(action, seq) \
    BOOST_PP_SEQ_FOR_EACH(action, _, BOOST_PP_SEQ_POP_FRONT(BOOST_PP_CAT(ANONYMOUS_TYPE_0(0,0)seq,_END))) \
/**/

#define NEW(seq) \
    [&] \
    { \
        FOR_EACH_DECL(DECLARE_VAR, seq)\
        struct \
        { \
            FOR_EACH_DECL(DECLARE_MEMBER, seq)\
        } anonymous = {FOR_EACH_DECL(MOVE_VAR, seq)}; \
        return anonymous; \
    }() \
/**/

int main()
{
    auto scope_value = 123;
    auto xs = make_vector
    (
        NEW((y, 0.5)(x, scope_value + 1)),
        NEW((x, 0.05)(y, 10)(p,0.001))
    );
    for_each(xs, [](auto x)
    {
        cout << "x.x = " << x.x << ", sizeof(x) = " << sizeof(x) << endl;
    });
}
