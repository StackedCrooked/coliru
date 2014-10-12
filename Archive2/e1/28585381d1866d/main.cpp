// Copyright Evgeny Panasyuk 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// e-mail: E?????[dot]P???????[at]gmail.???

// Compile-time template engine

// GOTO main

#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/apply.hpp>
#include <initializer_list>
#include <cstddef>
#include <utility>

namespace CTTE
{
    /************************************************************************************************/
    // boost utils

    template<typename Lambda, typename X>
    auto make_pair(Lambda, X x)
    {
        return boost::fusion::make_pair<Lambda>(std::move(x));
    }

    template<typename Lambda, typename ...Ts>
    using mpl_apply = typename boost::mpl::apply<Lambda, Ts...>::type;
    /************************************************************************************************/
    // null terminated string utils

    template<typename I, typename T>
    constexpr I find(I first, T x)
    {
        return *first == x ? first : find(first+1, x);
    }
    /* C++14
    template<typename I, typename T>
    constexpr I find(I first, T x)
    {
        while(*first != x)
            ++first;
        return first;
    }*/

    constexpr std::size_t c_str_length(const char *x)
    {
        return find(x, '\0') - x;
    }
    /************************************************************************************************/
    // Compile time string encoded in type

    template<char... cs>
    struct string_value
    {
        static constexpr const char value[sizeof...(cs)+1] = {cs..., '\0'};
    };
    template<char... cs>
    constexpr const char string_value<cs...>::value[sizeof...(cs)+1];

    template<char... cs>
    struct string
    {
        //using mpl_string = mpl::string<cs...>;
        using value_type = string_value<cs...>;
    };

    template<typename, typename> struct make_string_aux;

    template<typename String, std::size_t ...Is>
    struct make_string_aux<String, std::index_sequence<Is...>>
    {
        using type = string<String::value()[Is]...>;
    };

    template<typename String, std::size_t length = c_str_length(String::value())>
    using make_string = typename make_string_aux
    <
        String, std::make_index_sequence<length>
    >::type;
    /************************************************************************************************/
    // Split string by delimiter into prefix = [first, delimiter),
    // and suffix = (delimiter, last]

    template<typename String, char delimiter, typename Prefix = string<>>
    struct split_string;

    template<char... suffix_cs, char delimiter, char... prefix_cs>
    struct split_string
    <
        string<delimiter, suffix_cs...>,
        delimiter,
        string<prefix_cs...>
    >
    {
        using prefix = string<prefix_cs...>;
        using suffix = string<suffix_cs...>;
    };

    template<char first, char... suffix_cs, char delimiter, char... prefix_cs>
    struct split_string
    <
        string<first, suffix_cs...>,
        delimiter,
        string<prefix_cs...>
    >
    {
        using aux = split_string
        <
            string<suffix_cs...>,
            delimiter,
            string<prefix_cs..., first>
        >;
        using prefix = typename aux::prefix;
        using suffix = typename aux::suffix;
    };

    template<char delimiter, char... prefix_cs>
    struct split_string<string<>, delimiter, string<prefix_cs...>>
    {
        using prefix = string<prefix_cs...>;
        using suffix = string<>;
    };
    /************************************************************************************************/
    template<typename...> struct vector {};

    template<typename String, typename Actions, typename ParsedActions = vector<>>
    struct split_by_actions;

    template<typename String, typename CurrentAction, typename ...Actions, typename ...ParsedActions>
    struct split_by_actions
    <
        String,
        vector<CurrentAction, Actions...>,
        vector<ParsedActions...>
    >
    {
        using splited = split_string<String, '$'>;
        using action = mpl_apply<CurrentAction, typename splited::prefix>;
        using shifted_actions = vector<Actions..., CurrentAction>;

        using type = typename split_by_actions
        <
            typename splited::suffix,
            shifted_actions,
            vector<ParsedActions..., action>
        >::type;
    };

    template<typename CurrentAction, typename ...Actions, typename ...ParsedActions>
    struct split_by_actions<string<>, vector<CurrentAction, Actions...>, vector<ParsedActions...>>
    {
        using type = vector<ParsedActions...>;
    };
    /************************************************************************************************/
    #define CTTE_WRAP_STRING(x) \
        [] \
        { \
            struct { static constexpr auto value() { return x;} } str; \
            return str; \
        } \
    /**/
    #define CTTE_STRING_HOLDER(X) decltype(std::declval<X>()())
    #define CTTE_MAKE_STRING(X) CTTE::make_string<CTTE_STRING_HOLDER(X)>

    #define CTTE_CAPTURE_VAR(x) CTTE::make_pair(CTTE_WRAP_STRING(#x), &x)
    #define CTTE_CAPTURE_VAR_AUX(r, data, elem) , CTTE_CAPTURE_VAR(elem)
    /************************************************************************************************/   
    template<typename ...Pairs>
    auto make_context(Pairs... pairs)
    {
        return boost::fusion::make_map
        <
            CTTE_MAKE_STRING(typename Pairs::first_type)...
        >(std::move(pairs.second)...);
    };
    /************************************************************************************************/
    template<typename Action, typename ...Actions, typename Context, typename F>
    auto apply_actions(vector<Action, Actions...>, Context context, F f)
    {
        return apply_actions(vector<Actions...>{}, context, Action{}(context, f));
    }

    template<typename Context, typename F>
    auto apply_actions(vector<>, Context, F f)
    {
        return f;
    }

    /* Non-recursion version, but with different semantics:
    template<typename ...Actions, typename Context, typename F>
    void apply_actions(vector<Actions...>, Context context, F f)
    {
        (void)initializer_list<int>{( Actions{}(context, f) , 0)...};
        return f;
    }*/
    /************************************************************************************************/
    template<typename String>
    struct StringAction
    {
        template<typename Context, typename F>
        F operator()(Context, F f)
        {
            f( String::value_type::value );
            return f;
        }
    };

    template<typename Variable>
    struct VariableAction
    {
        template<typename Context, typename F>
        F operator()(Context context, F f)
        {
            BOOST_MPL_ASSERT_MSG
            (
                (boost::fusion::result_of::has_key<Context, Variable>::type::value),
                WRONG_VARIABLE_NAME_IN_FORMAT_STRING,
                (Variable)
            );

            f( *boost::fusion::at_key<Variable>(context) );
            return f;
        }
    };

    template<typename Format>
    using make_actions = typename split_by_actions
    <
        Format,
        vector<StringAction<boost::mpl::_>, VariableAction<boost::mpl::_>>
    >::type;
    /************************************************************************************************/
    // function-like version:

    template<typename F, typename Format, typename ...Pairs>
    auto process_format_aux(F f, Format, Pairs... pairs)
    {
        return apply_actions
        (
            make_actions<CTTE_MAKE_STRING(Format)>{},
            make_context(pairs...),
            std::move(f)
        );
    }

    #define process_format(f, format, ...) \
        CTTE::process_format_aux \
        ( \
            f, \
            CTTE_WRAP_STRING(format) \
            BOOST_PP_SEQ_FOR_EACH(CTTE_CAPTURE_VAR_AUX, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
        ) \
    /**/
    /************************************************************************************************/
    // for-like version:

    template<typename Context, typename Format>
    struct for_each_part_aux_operator
    {
        Context context;
        template<typename F>
        F operator*(F f)
        {
            return apply_actions(make_actions<CTTE_MAKE_STRING(Format)>{}, context, std::move(f));
        }
    };

    template<typename Format, typename ...Pairs>
    auto for_each_part_aux(Format, Pairs... pairs)
    {
        auto context = make_context(pairs...);
        return for_each_part_aux_operator<decltype(context), Format>{std::move(context)};
    }
    #define for_each_part(loop_parameter, format, ...) \
        CTTE::for_each_part_aux \
        ( \
            CTTE_WRAP_STRING(format) \
            BOOST_PP_SEQ_FOR_EACH(CTTE_CAPTURE_VAR_AUX, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
        ) * [&](loop_parameter)\
    /**/
} // namespace end
/************************************************************************************************/
#include <iostream>

#ifdef __GNUC__
    #define NOINLINE __attribute__((noinline))
#else
    #define NOINLINE
#endif

template<typename T>
NOINLINE void print_it(T x)
#if 1
{
    std::cout << x;
}
#else
;
#endif

NOINLINE void test_handwritten()
{
    int counter = 2;
    char character = '!';
    double value = 0.5;

    print_it("val = ");
    print_it(value);
    print_it(", cnt = ");
    print_it(counter);
    print_it(", ch = ");
    print_it(character);
    print_it(", again v=");
    print_it(value);
    print_it(";\n");
}

NOINLINE void test_process_format()
{
    int counter = 2;
    char character = '!';
    double value = 0.5;

    auto print = [](auto x)
    {
        print_it(x);
    };
    process_format(print, "val = $value$, cnt = $counter$, ch = $character$, again v=$value$;\n", counter, character, value);
}

NOINLINE void test_for_each_part()
{
    int counter = 2;
    char character = '!';
    double value = 0.5;

    for_each_part(auto x, "val = $value$, cnt = $counter$, ch = $character$, again v=$value$;\n", counter, character, value)
    {
        print_it(x);
    };
}

int main()
{
    test_handwritten();
    test_process_format();
    test_for_each_part();
}
