
//START of BOOST_SWITCH.HPP
// switch.hpp
//
// Copyright (c) 2006-2007
// Steven Watanabe
//
// Distriuted under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost/org/LICENSE_1_0.txt)

#ifndef BOOST_SWITCH_HPP_INCLUDED
#define BOOST_SWITCH_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/preprocessor/config/limits.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/type_traits/remove_reference.hpp>

#ifndef BOOST_SWITCH_LIMIT
    #define BOOST_SWITCH_LIMIT 50
#endif

#if BOOST_SWITCH_LIMIT > BOOST_PP_LIMIT_REPEAT
    #error BOOST_SWITCH_LIMIT exceeds Boost.Preprocessor limit
#endif
#if BOOST_SWITCH_LIMIT > BOOST_PP_LIMIT_ITERATION
    #error BOOST_SWITCH_LIMIT exceeds Boost.Preprocessor limit
#endif

namespace boost {

class bad_switch : public std::runtime_error {
public:
    template<class Int>
    explicit bad_switch(Int v) :
        std::runtime_error(
            "boost::switch_ default case called -- none provided. value is: " +
            boost::lexical_cast<std::string>(v)) {}
};

namespace switch_detail {

// Avoid the need to create all the specializations of switch_impl
// twice. Just pass this to switch_impl<N>::apply(...) when no
// default is supplied.

template<class R>
inline R forced_return(typename boost::remove_reference<R>::type* r = 0) {
    return(*r);
}

// Thanks to Stjepan Rajko for catching this.
template<>
inline void forced_return<void>(void*) {}
template<>
inline const void forced_return<const void>(const void*) {}
template<>
inline volatile void forced_return<volatile void>(volatile void*) {}
template<>
inline const volatile void forced_return<const volatile void>(const volatile void*) {}

template<class R>
struct throw_exception {
    template<class Int>
    R operator()(Int i) const {
        boost::throw_exception(bad_switch(i));
        return(switch_detail::forced_return<R>());
    }
};

// N is the number of cases not including the default
template<int N>
struct switch_impl;

// specialize for 0 separately to avoid warnings
template<>
struct switch_impl<0> {
    template<class V, class Int, class F, class Default>
    static typename F::result_type
    apply(Int i, F, Default d BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(V)) {
        return(d(i));
    }
};

#define BOOST_SWITCH_CASE(z, n, data)                   \
    case boost::mpl::at_c<data, n>::type::value: {      \
        typename boost::mpl::at_c<data, n>::type arg;   \
        return(f(arg));                                 \
    }

#define BOOST_SWITCH_IMPL(z, n, data)                                   \
    template<>                                                          \
    struct switch_impl<n> {                                             \
        template<class V, class I, class F, class D>                    \
        static typename F::result_type                                  \
        apply(I i, F f, D d BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(V)) {   \
            switch(i) {                                                 \
                BOOST_PP_REPEAT_##z(n, BOOST_SWITCH_CASE, V)            \
                default: return(d(i));                                  \
            }                                                           \
        }                                                               \
    };

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_SWITCH_LIMIT)
#define BOOST_PP_LOCAL_MACRO(n) BOOST_SWITCH_IMPL(1, n, ~)
#include BOOST_PP_LOCAL_ITERATE()

#undef BOOST_SWITCH_IMPL
#undef BOOST_SWITCH_CASE

}

template<class V, class N, class F>
inline typename F::result_type
switch_(N n, F f BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(V)) {
    typedef switch_detail::switch_impl<boost::mpl::size<V>::value> impl;
    switch_detail::throw_exception<typename F::result_type> default_;
    return(impl::template apply<V>(n, f, default_));
}

template<class V, class N, class F, class D>
inline typename F::result_type
switch_(N n, F f, D d BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(V)) {
    typedef switch_detail::switch_impl<boost::mpl::size<V>::value> impl;
    return(impl::template apply<V>(n, f, d));
}

}

#endif
//END  of  BOOST_SWITCH.HPP

#include <iostream>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/mpl/range_c.hpp>

namespace fusion=boost::fusion;
namespace mpl=boost::mpl;

template<typename FusionSequence, typename F>
struct handle_cases {
    typedef void result_type;
    template<typename Case>
    void operator()(Case) const {
        f(fusion::at<Case>(sequence));
    }
    handle_cases(const FusionSequence& s, F f) : sequence(s),f(f) {}
    const FusionSequence& sequence;
    F f;
};

template <typename FusionSequence, typename F>
void do_with_nth(const FusionSequence& seq, F f, int n)
{
    typedef typename fusion::result_of::size<FusionSequence>::type size;
    typedef mpl::range_c<std::size_t, 0, size::value> range;
    boost::switch_<range>(n, handle_cases<FusionSequence,F>(seq,f),[](auto i){});
}

//I think the following would be equivalent
/*template <typename FusionSequence, typename F>
void do_with_nth(const FusionSequence& seq, F f, int n)
{

    switch(n)
    {
        case 0: f(fusion::at_c<0>(seq));break;
        case 1: f(fusion::at_c<1>(seq));break;
        case 2: f(fusion::at_c<2>(seq));break;
        case 3: f(fusion::at_c<3>(seq));break;
    }
}*/

int main()
{
    std::tuple<int,float,double,bool> possible_types;
    for(int i=0; i < 4; ++i)
        do_with_nth(possible_types,[](auto val){ std::cout << typeid(val).name() << std::endl;},i);

}
