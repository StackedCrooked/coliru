#include <boost/typeof/typeof.hpp>

template<typename A, typename B>
struct result_of_conditional
{
    typedef BOOST_TYPEOF_TPL(true?A():B()) type;
};

template<typename A, typename B>
typename result_of_conditional<A, B>::type add(const A& a,const B& b)
{
    return a + b;
}