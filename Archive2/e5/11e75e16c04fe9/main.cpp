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


struct void_type {};

template<typename T>
struct result
{
    T value;

    template<class F>
    result &&operator*(const F&) &&
    {
        return std::move(*this);
    }
};

template<typename F, bool enable>
using enable_on_void_return =
    std::enable_if_t<enable == std::is_same<decltype(std::declval<F>()()), void>::value>;

template<typename F>
auto make_result(F &&calc, enable_on_void_return<F, false>* = 0)
{
    return result<std::decay_t<decltype(calc())>>{calc()};
}

template<typename F>
auto make_result(F &&calc, enable_on_void_return<F, true>* = 0)
{
    calc();
    return result<void_type>{};
}

template<typename Context>
struct trampoline
{
    Context context;

    template<class F>
    auto operator*(F &&f) const
    {
        return make_result([&]{ return context(f); });
    }
};

struct yes
{
    template<class Context>
    auto operator*(Context &&context) const
    {
        return trampoline<std::decay_t<Context>>{std::forward<Context>(context)};
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

struct extract_result
{
    template<typename T>
    auto operator+(result<T> &&x) const
    {
        return std::move(x.value);
    }
    void operator+(result<void_type> &&) const {}
    void operator+(const no &) const {}
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
    [&](auto &static_if_lambda_preface_long_aux_name) \
    { \
        return static_if_lambda_preface_long_aux_name( VARIADIC_FOR_EACH_I(CAPTURE_PASS, capture) ); \
    } * \
    []( VARIADIC_FOR_EACH_I(CAPTURE_PARAMS, capture) ) \
/**/

#define IF_AUX(capture, ...) static_if( __VA_ARGS__ () ) * LAMBDA_PREFACE(capture)
#define IF(...) extract_result{} + IF_AUX( __VA_ARGS__ )
#define ELSE_IF(capture, ...) * IF_AUX(capture, __VA_ARGS__)
#define ELSE(...) * yes{} * LAMBDA_PREFACE((__VA_ARGS__))

/**************************************************************************************/
// Example of usage:
#include <iostream>
#include <string>

using namespace std;

template<typename T>
auto test(const T &x)
{
    int local;

    return IF((x, local), is_same<T, std::string>)
    {
        cout << "string: \"" << x << "\" of size=" << x.size() << "\t";
        int &z = local;
        return "string branch"s;
    }
    ELSE_IF((x), is_same<T, int>)
    {
        cout << "integer: " << x << "\t";
        const int &z = x;
        return "integer branch";
    }
    ELSE(x, local)
    {
        cout << "else: " << x << "\t";
        int &z = local;
        return 'E';
    };
}

int main()
{
    cout << test(1) << endl;
    cout << test(0.5) << endl; 
    cout << test("Elbereth"s) << endl;
}
