#ifndef CONCEPT_TOOLKIT_HPP_INCLUDED
#define CONCEPT_TOOLKIT_HPP_INCLUDED

#include <utility>
#include <type_traits>

// With thanks to Rapptz

namespace Concepts {

/* Metaprogramming helpers */
namespace detail {

template<typename... Types> struct void_t { using type = void; };
template<typename... Types> using  void_ = typename void_t<Types...>::type;

template<typename Type> struct identity_t { using type = Type; };

template<typename... Conds>
struct or_t: std::false_type {};

template<typename Cond, typename... Conds>
struct or_t<Cond, Conds...>: std::conditional_t<Cond::value, std::true_type, or_t<Conds...>> {};

template<typename... Conds>
using or_ = typename or_t<Conds...>::type;

template<typename... Conds>
struct and_t: std::true_type {};

template<typename Cond, typename... Conds>
struct and_t<Cond, Conds...>: std::conditional_t<Cond::value, and_t<Conds...>, std::false_type> {};

template<typename... Conds>
using and_ = typename and_t<Conds...>::type;

template<typename Cond>
using not_ = std::integral_constant<bool, !Cond::value>;

} // detail

/* Diagnostic machinery */
namespace detail {

template<typename Type>
struct diagnostic_type {};

template<typename Type> struct undiagnostic_t:                                identity_t<Type> {};
template<typename Type> struct undiagnostic_t<diagnostic_type<Type>>:         identity_t<Type> {};
template<typename Type> struct undiagnostic_t<diagnostic_type<Type>&>:        identity_t<Type&> {};
template<typename Type> struct undiagnostic_t<diagnostic_type<Type> const&>:  identity_t<Type const&> {};
template<typename Type> struct undiagnostic_t<diagnostic_type<Type>&&>:       identity_t<Type&&> {};
template<typename Type> struct undiagnostic_t<diagnostic_type<Type> const&&>: identity_t<Type const&&> {};
template<typename Type> using  undiagnostic = typename undiagnostic_t<Type>::type;

template<typename Type> struct is_unqualified_diagnostic: std::false_type {};
template<typename Type> struct is_unqualified_diagnostic<diagnostic_type<Type>>: std::true_type {};

template<typename Type>
struct is_diagnostic
: is_unqualified_diagnostic<std::remove_cv_t<std::remove_reference_t<Type>>> {};

} // detail

template<typename Type>
constexpr detail::diagnostic_type<Type> diagnostic(Type&& type) noexcept;

/* Concept requirements */

// Boolean atom (conjunct to the requires clause)
template<bool Cond>
struct boolean;

// Expression requirement expectations
struct valid;
template<typename Type> struct explicit_;
template<typename Type> struct exact;
template<template<typename...> class ConceptAlias> struct models;

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
namespace detail {

template<typename Concept, typename Sfinae = void>
struct well_formed_requirements: std::false_type {};

template<template<typename...> class Concept, typename... Args>
struct well_formed_requirements<
    Concept<Args...>
    , void_<decltype( Concept<Args...> {}.requires(std::declval<Args>()...) )>
>: std::true_type {};

template<typename Requirement>
struct requirement_case {
    static_assert( (identity_t<Requirement> {}, false), "Concept syntax error" );
};

template<bool Cond>
struct requirement_case<boolean<Cond>>:           identity_t<all_of<boolean<Cond>>> {};

template<typename Expr, typename Expected>
struct requirement_case<expr<Expr, Expected>>:    identity_t<all_of<expr<Expr, Expected>>> {};

template<typename Type>
struct requirement_case<type<Type>>:              identity_t<all_of<type<Type>>> {};

template<typename... Nested>
struct requirement_case<nested<Nested...>>:       identity_t<all_of<nested<Nested...>>> {};

template<typename... Requirements>
struct requirement_case<all_of<Requirements...>>: identity_t<all_of<Requirements...>> {};

} // detail

template<typename Concept, typename Sfinae = void>
struct requirements_t {};

template<template<typename...> class Concept, typename... Args>
struct requirements_t<
    Concept<Args...>
    , detail::void_<decltype( Concept<Args...> {}.requires(std::declval<Args>()...) )>
>: detail::requirement_case<decltype( Concept<Args...> {}.requires(std::declval<Args>()...) )> {};

template<typename Concept>
using requirements = typename requirements_t<Concept>::type;

template<typename Concept>
using safe_requirements = typename std::conditional_t<
    detail::well_formed_requirements<Concept>::value
    , requirements_t<Concept>
    , detail::identity_t<all_of<>>
>::type;

// Expand requirement list into variadic pack
namespace detail {
template<template<typename...> class Check, typename Concept, typename Reqs>
struct bind_over;

template<template<typename...> class Check, typename Concept, typename... Reqs>
struct bind_over<Check, Concept, all_of<Reqs...>> {
    using type = Check<Concept, Reqs...>;
};
} // detail

/* Check requirements (SFINAE-friendly, soft errors) */
template<typename Concept, typename... Requirements>
struct check;

template<typename Concept>
using Check = std::conditional_t<
    detail::well_formed_requirements<Concept>::value
    , typename detail::bind_over<
        check
        , Concept
        , safe_requirements<Concept>
    >::type
    , std::false_type
>;

template<typename Concept>
struct check<Concept>: std::true_type {};

template<typename Concept, bool Cond, typename... Rest>
struct check<Concept, boolean<Cond>, Rest...>
: std::conditional_t<Cond, check<Concept, Rest...>, std::false_type> {};

template<typename Concept, typename Expr, typename... Rest>
struct check<Concept, expr<Expr>, Rest...>
: check<Concept, Rest...> {};

template<typename Concept, typename Expr, typename Expected, typename... Rest>
struct check<Concept, expr<Expr, Expected>, Rest...>
: std::conditional_t<
    std::is_convertible<Expr, Expected>::value
    , check<Concept, Rest...>
    , std::false_type
> {};

template<typename Concept, typename Expr, typename Expected, typename... Rest>
struct check<Concept, expr<Expr, explicit_<Expected>>, Rest...>
: std::conditional_t<
    std::is_constructible<Expected, Expr>::value
    , check<Concept, Rest...>
    , std::false_type
> {};

template<typename Concept, typename Expr, typename Expected, typename... Rest>
struct check<Concept, expr<Expr, exact<Expected>>, Rest...>
: std::conditional_t<
    std::is_same<Expected, Expr>::value
    , check<Concept, Rest...>
    , std::false_type
> {};

template<typename Concept, typename Expr, template<typename...> class Expected, typename... Rest>
struct check<Concept, expr<Expr, models<Expected>>, Rest...>
: std::conditional_t<
    Check<Expected<Expr>>::value
    , check<Concept, Rest...>
    , std::false_type
> {};

template<typename Concept, typename Type, typename... Rest>
struct check<Concept, type<Type>, Rest...>
: check<Concept, Rest...> {};

template<typename Concept, typename... Nested, typename... Rest>
struct check<Concept, nested<Nested...>, Rest...>
: std::conditional_t<
    detail::and_<Check<Nested>...>::value
    , check<Concept, Rest...>
    , std::false_type
> {};

/* Diagnose requirements (assertions, hard errors) */
template<typename Concept>
struct bad_concept_instantiation {
    static_assert( (detail::identity_t<Concept> {}, false)
            , "\n\n\t\t=====> Concept exhibits invalid expression or associated type <=====\n\n" );
};

template<typename Concept, typename... Requirements>
struct diagnose;

template<typename Concept>
using Diagnose = std::conditional_t<
    detail::well_formed_requirements<Concept>::value
    , typename detail::bind_over<
        diagnose
        , Concept
        , safe_requirements<Concept>
    >::type
    , bad_concept_instantiation<Concept>
>;

template<typename Concept>
struct diagnose<Concept> {};

template<typename Concept, bool Cond, typename... Rest>
struct diagnose<Concept, boolean<Cond>, Rest...>
: diagnose<Concept, Rest...> {
    static_assert( Cond
            , "\n\n\t\t=====> Condition was not fulfilled <=====\n\n" );
};

template<typename Concept, typename Expr, typename... Rest>
struct diagnose<Concept, expr<Expr>, Rest...>
: diagnose<Concept, Rest...> {};

template<typename Concept, typename Expr, typename Expected, typename... Rest>
struct diagnose<Concept, expr<Expr, Expected>, Rest...>
: diagnose<Concept, Rest...> {
    static_assert( std::is_convertible<Expr, Expected>()
            , "\n\n\t\t=====> Expression is not implicitly convertible to expected type <=====\n\n" );
};

template<typename Concept, typename Expr, typename Expected, typename... Rest>
struct diagnose<Concept, expr<Expr, explicit_<Expected>>, Rest...>
: diagnose<Concept, Rest...> {
    static_assert( std::is_constructible<Expected, Expr>()
            , "\n\n\t\t=====> Expression is not explicitly convertible to expected type <=====\n\n" );
};

template<typename Concept, typename Expr, typename Expected, typename... Rest>
struct diagnose<Concept, expr<Expr, exact<Expected>>, Rest...>
: diagnose<Concept, Rest...> {
    static_assert( std::is_same<Expected, Expr>()
            , "\n\n\t\t=====> Expression does not have expected type <=====\n\n" );
};

template<typename Concept, typename Expr, template<typename...> class Expected, typename... Rest>
struct diagnose<Concept, expr<Expr, models<Expected>>, Rest...>
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// sadly this produces a somewhat incomplete template instantiation stack with GCC
: Diagnose<Expected<Expr>>, diagnose<Concept, Rest...> {
    // A fallback that asks of the user to Diagnose<Expected<Expr>> themselves to get
    // any more information:
    //
    // static_assert( Check<Expected<Expr>>()
    //        , "\n\n\t\t=====> Expression is not a model of expected concept <=====\n\n" );
};

template<typename Concept, typename Type, typename... Rest>
struct diagnose<Concept, type<Type>, Rest...>
: diagnose<Concept, Rest...> {};

template<typename Concept, typename... Nested, typename... Rest>
struct diagnose<Concept, nested<Nested...>, Rest...>
: private Diagnose<Nested>..., diagnose<Concept, Rest...> {};

/* Choose between checks (soft errors) or diagnostics (hard errors) */
template<typename Concept, typename Sfinae = std::true_type>
struct check_or_diagnose;

template<template<typename...> class Concept, typename... Args>
struct check_or_diagnose<
    Concept<Args...>
    , detail::not_<detail::or_<detail::is_diagnostic<Args>...>>
>: Check<Concept<Args...>> {};

template<template<typename...> class Concept, typename... Args>
struct check_or_diagnose<
    Concept<Args...>
    , detail::or_<detail::is_diagnostic<Args>...>
>: private Diagnose<Concept<detail::undiagnostic<Args>...>>
, std::true_type
{};

// Make it easy to bring into scope those names useful for writing concepts and those only
namespace Toolkit {

using Concepts::valid;
using Concepts::explicit_;
using Concepts::exact;
using Concepts::models;

using Concepts::boolean;
using Concepts::expr;
using Concepts::type;
using Concepts::nested;
using Concepts::all_of;

} // Toolkit

/* Constrain function templates */
enum struct enabled {};

namespace detail {
struct empty_type {};
} // detail

template<typename... Concepts>
struct requires;

template<>
struct requires<>: detail::identity_t<enabled> {};

template<typename Concept, typename... Concepts>
struct requires<Concept, Concepts...>
: std::conditional_t<check_or_diagnose<Concept>::value, requires<Concepts...>, detail::empty_type> {};

template<typename... Concepts>
using Requires = typename requires<Concepts...>::type;

} // Concepts

#endif /* CONCEPT_TOOLKIT_HPP_INCLUDED */