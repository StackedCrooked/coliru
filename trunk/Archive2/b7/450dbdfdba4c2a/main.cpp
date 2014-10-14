// Emulation of "static if" feature from D language within function body, alpha version
// Original idea by Maxim Yanchenko (refer http://rsdn.ru/forum/cpp/5816278.flat.1)
// Improvements by Evgeny Panasyuk

/**************************************************************************************/
// Implementation:
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <type_traits>
#include <utility>

struct noop
{
    template<class F>
    noop operator*(const F&) const
    {
        return noop{};
    }
};

template<typename Context>
struct trampoline
{
    Context context;

    template<class F>
    auto operator*(F f) const
    {
        context(std::move(f));
        return noop{};
    }
};

struct yes
{
    template<class Context>
    auto operator*(Context context) const
    {
        return trampoline<Context>{std::move(context)};
    }
};

struct no
{
    auto operator*(yes) const
    {
        return yes{};
    }

    template<class F>
    auto operator*(const F&) const
    {
        return no{};
    }
};

auto static_if(std::true_type)
{
    return yes{};
}

auto static_if(std::false_type)
{
    return no{};
}

#define CAPTURE_PASS(r, data, i, elem) BOOST_PP_COMMA_IF(i) elem
#define CAPTURE_PARAMS(r, data, i, elem) BOOST_PP_COMMA_IF(i) auto &elem

#define VARIADIC_FOR_EACH_I_AUX(macro, elems) \
    BOOST_PP_SEQ_FOR_EACH_I(macro, _, elems) \
/**/

#define VARIADIC_FOR_EACH_I(macro, elems) \
    VARIADIC_FOR_EACH_I_AUX(macro, BOOST_PP_VARIADIC_TO_SEQ elems) \
/**/

#define LAMBDA_PREFACE(capture) \
    [&](auto static_if_lambda_preface_long_aux_name) \
    { \
        static_if_lambda_preface_long_aux_name( VARIADIC_FOR_EACH_I(CAPTURE_PASS, capture) ); \
    } * \
    []( VARIADIC_FOR_EACH_I(CAPTURE_PARAMS, capture) ) \
/**/

#define IF(capture, ...) static_if( __VA_ARGS__ () ) * LAMBDA_PREFACE(capture)
#define ELSE_IF(capture, ...) * IF(capture, __VA_ARGS__)
#define ELSE(...) * yes{} * LAMBDA_PREFACE((__VA_ARGS__))

/**************************************************************************************/
// Example of usage:
#include <iostream>
#include <string>

using namespace std;

template<typename T>
void test(const T &x)
{
    int local;

    IF((x, local), is_same<T, std::string>)
    {
        cout << "string: \"" << x << "\" of size=" << x.size() << endl;
        int &z = local;
    }
    ELSE_IF((x), is_same<T, int>)
    {
        cout << "integer: " << x << endl;
        const int &z = x;
    }
    ELSE(x, local)
    {
        cout << "else: " << x << endl;
        int &z = local;
    };
}

int main()
{
    test(1);
    test(0.5);
    test("Elbereth"s);
}