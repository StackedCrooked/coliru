// Copyright Evgeny Panasyuk 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// e-mail: E?????[dot]P???????[at]gmail.???

// Emulation of "Anonymous Types"

// GOTO main

#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/pop_front.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <iostream>
#include <utility>

/************************************************************************************************/
// refer http://www.boost.org/doc/libs/1_56_0/boost/fusion/adapted/struct/define_struct.hpp
// rerquired for sequence of tuples syntax ((a,b)(c,d)...)
#define ANONYMOUS_TYPE_0(X, Y) ((X, Y)) ANONYMOUS_TYPE_1
#define ANONYMOUS_TYPE_1(X, Y) ((X, Y)) ANONYMOUS_TYPE_0
#define ANONYMOUS_TYPE_0_END
#define ANONYMOUS_TYPE_1_END

#define VAR_NAME(elem) BOOST_PP_TUPLE_ELEM(2, 0, elem)
#define VAR_VALUE(elem) BOOST_PP_TUPLE_ELEM(2, 1, elem)
#define VALUES(r, data, i, elem) BOOST_PP_COMMA_IF(i) VAR_VALUE(elem)
#define DECLARE_MEMBER(r, data, i, elem) typename boost::mpl::at_c<Ts, i>::type VAR_NAME(elem);

#define FOR_EACH_DECL(action, seq) \
    BOOST_PP_SEQ_FOR_EACH_I(action, _, BOOST_PP_SEQ_POP_FRONT(BOOST_PP_CAT(ANONYMOUS_TYPE_0(0,0)seq,_END))) \
/**/

#define NEW_AUX(seq) \
    [](auto... args) \
    { \
        using Ts = boost::mpl::vector<decltype(args)...>; \
        struct \
        { \
            FOR_EACH_DECL(DECLARE_MEMBER, seq)\
        } anonymous = {std::move(args)...}; \
        return anonymous; \
    } \
/**/

#define NEW_LAZY(seq) (boost::phoenix::bind(NEW_AUX(seq), FOR_EACH_DECL(VALUES, seq)))
#define NEW(seq) (NEW_AUX(seq)(FOR_EACH_DECL(VALUES, seq)))
/************************************************************************************************/
int main()
{
    using namespace std;
    using namespace boost;
    using phoenix::arg_names::_1;

    auto scope_value = 123;
    
    cout << "NEW demo:" << endl;
    auto xs = fusion::make_vector
    (
        NEW((y, 0.5)(x, scope_value + 1)),
        NEW((x, 0.05)(y, 10)(p, 0.001))
    );
    fusion::for_each(xs, [](auto x)
    {
        cout <<  "x.x = " << x.x << ", sizeof(x) = " << sizeof(x) << endl;
    });
    
    cout << endl << "NEW_LAZY demo:" << endl;
    fusion::for_each(transform(xs, NEW_LAZY((y, scope_value + 11)(q, _1))), [](auto x)
    {
        cout << "x.q.x = " << x.q.x << ", sizeof(x) = " << sizeof(x) << endl;
    });
}
