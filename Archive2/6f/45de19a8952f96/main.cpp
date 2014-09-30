#ifndef CONCEPTS_TOOLKIT_HPP_INCLUDED
#define CONCEPTS_TOOLKIT_HPP_INCLUDED

#include <type_traits>

// With thanks to Rapptz

namespace Concepts {

/* Metaprogramming helpers */
struct empty_type {};

template<typename... Types> struct void_ { using type = void; };
template<typename... Types> using  void_t = typename void_<Types...>::type;

template<typename Type> struct identity { using type = Type; };

template<typename... Conds>
struct or_: std::false_type {};

template<typename Cond, typename... Conds>
struct or_<Cond, Conds...>: std::conditional_t<Cond::value, std::true_type, or_<Conds...>> {};

template<typename Cond>
struct not_: std::integral_constant<bool, !Cond::value> {};

template<typename Type> using unqualified_t = std::remove_cv_t<std::remove_reference_t<Type>>;

/* Diagnostic machinery */
template<typename Type>
struct diagnostic_type {};

template<typename Type> struct undiagnose:                                identity<Type> {};
template<typename Type> struct undiagnose<diagnostic_type<Type>>:         identity<Type> {};
template<typename Type> struct undiagnose<diagnostic_type<Type>&>:        identity<Type&> {};
template<typename Type> struct undiagnose<diagnostic_type<Type> const&>:  identity<Type const&> {};
template<typename Type> struct undiagnose<diagnostic_type<Type>&&>:       identity<Type&&> {};
template<typename Type> struct undiagnose<diagnostic_type<Type> const&&>: identity<Type const&&> {};
template<typename Type> using  undiagnose_t = typename undiagnose<Type>::type;

template<typename Type> struct is_diagnostic_unqualified: std::false_type {};
template<typename Type> struct is_diagnostic_unqualified<diagnostic_type<Type>>: std::true_type {};

template<typename Type>
struct is_diagnostic: is_diagnostic_unqualified<unqualified_t<Type>> {};

template<typename Type>
constexpr diagnostic_type<Type> diagnose(Type&& type) noexcept;

/* Concept requirements */

// Boolean atom (conjunct to the requires clause)
template<bool Cond>
struct boolean;

// Expression requirements expectations
struct valid;
template<typename Type> struct explicit_;
template<typename Type> struct exact;
template<template<typename...> class Concept> struct models;

// Expression (aka compound) requirement
template<typename Expr, typename Expected = valid>
struct expr;

// Associated type requirement
template<typename Type>
struct type;

// Nested requirement
template<typename... Parents>
struct nested;

// Requirement list
template<typename... Requirements>
struct all_of;

/* Extract or query requirements from concept */
template<typename Concept, typename Sfinae = void>
struct has_requirements: std::false_type {};

template<template<typename...> class Concept, typename... Args>
struct has_requirements<Concept<Args...>, void_t<decltype( Concept<Args...> {}.requires(std::declval<Args>()...) )>>
: std::true_type {};

template<typename Requirement>
struct requirement_case {
    static_assert( (identity<Requirement> {}, false), "Concept syntax error" );
};

template<bool Cond>
struct requirement_case<boolean<Cond>>: identity<all_of<boolean<Cond>>> {};

template<typename Expr, typename Expected>
struct requirement_case<expr<Expr, Expected>>: identity<all_of<expr<Expr, Expected>>> {};

template<typename Type>
struct requirement_case<type<Type>>: identity<all_of<type<Type>>> {};

template<typename... Nested>
struct requirement_case<nested<Nested...>>: identity<all_of<nested<Nested...>>> {};

template<typename... Requirements>
struct requirement_case<all_of<Requirements...>>: identity<all_of<Requirements...>> {};

template<typename Concept, typename Sfinae = void>
struct requirements {};

template<template<typename...> class Concept, typename... Args>
struct requirements<Concept<Args...>, void_t<decltype( Concept<Args...> {}.requires(std::declval<Args>()...) )>>
: requirement_case<decltype( Concept<Args...> {}.requires(std::declval<Args>()...) )> {};

template<typename Concept>
using requirements_t = typename requirements<Concept>::type;

// Expand requirement list into variadic pack
namespace detail {
template<template<typename...> class Check, typename Reqs>
struct bind_over;

template<template<typename...> class Check, typename... Reqs>
struct bind_over<Check, all_of<Reqs...>> {
    template<typename... Prefix>
    struct with_prefix {
        template<typename... Suffix>
        struct with_suffix {
            using type = Check<Prefix..., Reqs..., Suffix...>;
        };

        using type = Check<Prefix..., Reqs...>;
    };

    template<typename... Suffix>
    struct with_suffix {
        using type = Check<Reqs..., Suffix...>;
    };

    using type = Check<Reqs...>;
};
} // detail

/* Check requirements (SFINAE-friendly, soft errors) */
template<typename Concept, typename Sfinae = void>
struct check_requirements: std::false_type {};

template<typename Sfinae, typename... Requirements>
struct check_all_requirements: std::false_type {};

template<>
struct check_all_requirements<void>: std::true_type {};

template<bool Cond, typename... Rest>
struct check_all_requirements<void, boolean<Cond>, Rest...>
: std::conditional_t<Cond, check_all_requirements<void, Rest...>, std::false_type> {};

template<typename Expr, typename... Rest>
struct check_all_requirements<void, expr<Expr>, Rest...>
: check_all_requirements<void, Rest...> {};

template<typename Expr, typename Expected, typename... Rest>
struct check_all_requirements<void, expr<Expr, Expected>, Rest...>
: std::conditional_t<
    std::is_convertible<Expr, Expected>::value
    , check_all_requirements<void, Rest...>
    , std::false_type
> {};

template<typename Expr, typename Expected, typename... Rest>
struct check_all_requirements<void, expr<Expr, explicit_<Expected>>, Rest...>
: std::conditional_t<
    std::is_constructible<Expected, Expr>::value
    , check_all_requirements<void, Rest...>
    , std::false_type
> {};

template<typename Expr, typename Expected, typename... Rest>
struct check_all_requirements<void, expr<Expr, exact<Expected>>, Rest...>
: std::conditional_t<
    std::is_same<Expected, Expr>::value
    , check_all_requirements<void, Rest...>
    , std::false_type
> {};

template<typename Expr, template<typename...> class Expected, typename... Rest>
struct check_all_requirements<void, expr<Expr, models<Expected>>, Rest...>
: std::conditional_t<
    check_requirements<Expected<Expr>>::value
    , check_all_requirements<void, Rest...>
    , std::false_type
> {};

template<typename Type, typename... Rest>
struct check_all_requirements<void, type<Type>, Rest...>
: check_all_requirements<void, Rest...> {};

template<typename... Rest>
struct check_all_requirements<void, nested<>, Rest...>
: check_all_requirements<void, Rest...> {};

template<typename Nested, typename... Nesteds, typename... Rest>
struct check_all_requirements<void_t<requirements_t<Nested>>, nested<Nested, Nesteds...>, Rest...>
: detail::bind_over<check_all_requirements, requirements_t<Nested>>
    ::template with_prefix<void>
    ::template with_suffix<nested<Nesteds...>, Rest...>
::type {};

template<typename Concept>
struct check_requirements<Concept, void_t<requirements_t<Concept>>>
: detail::bind_over<check_all_requirements, requirements_t<Concept>>
    ::template with_prefix<void>
::type {};

/* Diagnose requirements (assertions, hard errors) */
template<typename Concept, typename Sfinae = void>
struct diagnose_requirements;

template<typename... Requirements>
struct diagnose_all_requirements;

template<>
struct diagnose_all_requirements<> {};

template<bool Cond, typename... Rest>
struct diagnose_all_requirements<boolean<Cond>, Rest...>
: diagnose_all_requirements<Rest...> {
    static_assert( Cond
            , "\n\n\t\t:::::::::::::::::::::::::::::::::::::::"
                "\n\t\t:::::::::::::::::::::::::::::::::::::::"
                "\n\t\t::                                   ::"
                "\n\t\t::  ^ Condition was not fulfilled ^  ::"
                "\n\t\t::                                   ::"
                "\n\t\t:::::::::::::::::::::::::::::::::::::::"
                "\n\t\t:::::::::::::::::::::::::::::::::::::::\n" );
};

template<typename Expr, typename... Rest>
struct diagnose_all_requirements<expr<Expr>, Rest...>
: diagnose_all_requirements<Rest...> {};

template<typename Expr, typename Expected, typename... Rest>
struct diagnose_all_requirements<expr<Expr, Expected>, Rest...>
: diagnose_all_requirements<Rest...> {
    static_assert( std::is_convertible<Expr, Expected>()
            , "\n\n\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t::                                                                 ::"
                "\n\t\t::  ^ Expression is not implicitly convertible to expected type ^  ::"
                "\n\t\t::                                                                 ::"
                "\n\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n" );
};

template<typename Expr, typename Expected, typename... Rest>
struct diagnose_all_requirements<expr<Expr, explicit_<Expected>>, Rest...>
: diagnose_all_requirements<Rest...> {
    static_assert( std::is_constructible<Expected, Expr>()
            , "\n\n\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t::                                                                 ::"
                "\n\t\t::  ^ Expression is not explicitly convertible to expected type ^  ::"
                "\n\t\t::                                                                 ::"
                "\n\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n" );
};

template<typename Expr, typename Expected, typename... Rest>
struct diagnose_all_requirements<expr<Expr, exact<Expected>>, Rest...>
: diagnose_all_requirements<Rest...> {
    static_assert( std::is_same<Expected, Expr>()
            , "\n\n\t\t::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t::                                              ::"
                "\n\t\t::  ^ Expression does not have expected type ^  ::"
                "\n\t\t::                                              ::"
                "\n\t\t::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t::::::::::::::::::::::::::::::::::::::::::::::::::\n" );
};

template<typename Expr, template<typename...> class Expected, typename... Rest>
struct diagnose_all_requirements<expr<Expr, models<Expected>>, Rest...>
: diagnose_all_requirements<Rest...> {
    static_assert( check_requirements<Expected<Expr>>()
            , "\n\n\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t::                                                     ::"
                "\n\t\t::  ^ Expression is not a model of expected concept ^  ::"
                "\n\t\t::                                                     ::"
                "\n\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n" );
};

template<typename Type, typename... Rest>
struct diagnose_all_requirements<type<Type>, Rest...>
: diagnose_all_requirements<Rest...> {};

template<typename... Rest>
struct diagnose_all_requirements<nested<>, Rest...>
: diagnose_all_requirements<Rest...> {};

template<typename Nested, typename... Nesteds, typename... Rest>
struct diagnose_all_requirements<nested<Nested, Nesteds...>, Rest...>
: diagnose_requirements<Nested>
, detail::bind_over<
    diagnose_all_requirements
    , typename std::conditional_t<
        has_requirements<Nested>::value
        , requirements<Nested>
        , identity<all_of<>>
    >::type
>::template with_suffix<nested<Nesteds...>, Rest...>::type {};

template<typename Concept, typename Sfinae>
struct diagnose_requirements {
    static_assert( (identity<Concept> {}, false)
            , "\n\n\t\t::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t::                                                              ::"
                "\n\t\t::  ^ Concept exhibits invalid expression or associated type ^  ::"
                "\n\t\t::                                                              ::"
                "\n\t\t::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
                "\n\t\t::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n" );
};

template<typename Concept>
struct diagnose_requirements<Concept, void_t<requirements_t<Concept>>>
: detail::bind_over<diagnose_all_requirements, requirements_t<Concept>>::type {};

/* Choose between checks (soft errors) or diagnostics (hard errors) */
template<typename Concept, typename Sfinae = std::true_type>
struct concept_check;

template<template<typename...> class Concept, typename... Args>
struct concept_check<Concept<Args...>, typename not_<or_<is_diagnostic<Args>...>>::type>
: check_requirements<Concept<Args...>> {};

template<template<typename...> class Concept, typename... Args>
struct concept_check<Concept<Args...>, typename or_<is_diagnostic<Args>...>::type>
: private diagnose_requirements<Concept<undiagnose_t<Args>...>>
, std::true_type
{};

/* Constrain function templates */
enum struct enabled {};

template<typename... Concepts>
struct constraints;

template<>
struct constraints<>: identity<enabled> {};

template<typename Concept, typename... Concepts>
struct constraints<Concept, Concepts...>
: std::conditional_t<concept_check<Concept>::value, constraints<Concepts...>, empty_type> {};

template<typename... Concepts>
using Constraints = typename constraints<Concepts...>::type;

} // Concepts

#endif /* CONCEPTS_TOOLKIT_HPP_INCLUDED */