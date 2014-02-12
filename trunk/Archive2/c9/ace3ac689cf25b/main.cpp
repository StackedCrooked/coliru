#include <boost/preprocessor.hpp>
#include <iostream>
#include <typeinfo>

#ifndef TARASB_MAX_PARAMS
#define TARASB_MAX_PARAMS 8
#endif

#define TARASB_T(c,n) BOOST_PP_CAT(c, BOOST_PP_INC(n))
#define TARASB_TA(z, n, c) typename TARASB_T(c,n)
#define TARASB_A(z, n, c) TARASB_T(c,n)

#define TARASB_SIG_INFO_TYPEDEF(z, n, N) \
    typedef BOOST_PP_IF(BOOST_PP_LESS(n, N), TARASB_T(B, n), empty) \
    TARASB_T(A, n);

#define TARASB_SIG_INFO(z, n, unused) \
    template <typename RR BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM(n, TARASB_TA, B)> \
    struct sig_info<RR(BOOST_PP_ENUM(n, TARASB_A, B))> \
    { \
        enum { arg_count = n }; \
        typedef RR R; \
        BOOST_PP_REPEAT(TARASB_MAX_PARAMS, TARASB_SIG_INFO_TYPEDEF, n) \
    };

namespace tblib {

class empty {};

template <typename Sig>
struct sig_info
{
    enum { arg_count = -1 };
    typedef empty R;
    BOOST_PP_REPEAT(TARASB_MAX_PARAMS, TARASB_SIG_INFO_TYPEDEF, 0)
};

BOOST_PP_REPEAT(BOOST_PP_INC(TARASB_MAX_PARAMS), TARASB_SIG_INFO, ~)

}

#undef TARASB_T
#undef TARASB_TA
#undef TARASB_A
#undef TARASB_SIG_INFO_TYPEDEF
#undef TARASB_SIG_INFO


int main() {
    typedef tblib::sig_info<int (double, float)> info;

    std::cout << info::arg_count << std::endl;
    std::cout << typeid(info::R).name() << std::endl;
    std::cout << typeid(info::A1).name() << std::endl;
    std::cout << typeid(info::A2).name() << std::endl;
    std::cout << typeid(info::A3).name() << std::endl;
    return 0;
}