#include <iostream>
#include <tuple>
#include <vector>
#include <typeinfo>
#include <type_traits>



#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

std::string demangle(const char* name) {

    int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name ;
}

#else

// does nothing if not g++
std::string demangle(const char* name) {
    return name;
}

#endif

template <class T>
std::string type(const T& t) {
    return demangle(typeid(t).name());
}


/// \file meta.hpp Tiny meta-programming library.
//
// Meta library
//
//  Copyright Eric Niebler 2014-2015
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/meta
//

#ifndef META_HPP
#define META_HPP

#include <cstddef>
#include <type_traits>

/// \defgroup meta Meta
///
/// A tiny metaprogramming library

/// Tiny metaprogramming library
namespace meta
{
    /// \addtogroup meta
    /// @{

    namespace detail
    {
        /// Returns a \p T nullptr
        template <typename T> constexpr T *_nullptr_v() { return nullptr; }
    } // namespace detail

    template <typename T, T...> struct integer_sequence;

    template <typename... Ts> struct list;

    /// An empty type.
    struct nil_
    {
    };

    /// "Evaluate" the metafunction \p T by returning the nested \c T::type
    /// alias.
    template <typename T> using eval = typename T::type;

    /// Evaluate the Metafunction Class \p F with the arguments \p Args.
    template <typename F, typename... Args>
    using apply = typename F::template apply<Args...>;

    /// A Metafunction Class that always returns \p T.
    template <typename T> struct always
    {
       private:
        // Redirect through a class template for compilers that have not
        // yet implemented CWG 1558:
        // <http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#1558>
        template <typename...> struct impl
        {
            using type = T;
        };

       public:
        template <typename... Ts> using apply = eval<impl<Ts...>>;
    };

    /// An alias for `void`.
    template <typename... Ts> using void_ = apply<always<void>, Ts...>;

    /// \cond
    namespace detail
    {
        template <typename, typename = void> struct has_type_
        {
            using type = std::false_type;
        };

        template <typename T> struct has_type_<T, void_<typename T::type>>
        {
            using type = std::true_type;
        };

        template <typename, typename, typename = void> struct lazy_apply_
        {
        };

        template <typename F, typename... Ts>
        struct lazy_apply_<F, list<Ts...>, void_<apply<F, Ts...>>>
        {
            using type = apply<F, Ts...>;
        };
    } // namespace detail
    /// \endcond

    /// \brief An alias for `std::true_type` if `T::type` exists and names a
    /// type;
    ///        otherwise, it's an alias for `std::false_type`.
    template <typename T> using has_type = eval<detail::has_type_<T>>;

    /// A metafunction that evaluates the Metafunction Class \p F with
    /// the arguments \p Args.
    template <typename F, typename... Args>
    struct lazy_apply : detail::lazy_apply_<F, list<Args...>>
    {
    };

    /// An integral constant wrapper for \c std::size_t.
    template <std::size_t N>
    using size_t = std::integral_constant<std::size_t, N>;

    /// An integral constant wrapper for \c bool.
    template <bool B> using bool_ = std::integral_constant<bool, B>;

    /// A metafunction that always returns its argument \p T.
    template <typename T> struct id
    {
        using type = T;
    };

    /// A metafunction that is type \p T.
    template <typename T> using id_t = eval<id<T>>;

    /// Turn a class template or alias template \p C into a
    /// Metafunction Class.
    template <template <typename...> class C> struct quote
    {
       private:
        template <typename, typename = quote, typename = void> struct impl
        {
        };
        template <typename... Ts, template <typename...> class D>
        struct impl<list<Ts...>, quote<D>, void_<D<Ts...>>>
        {
            using type = D<Ts...>;
        };

       public:
        // Indirection here needed to avoid Core issue 1430
        // http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430
        template <typename... Ts> using apply = eval<impl<list<Ts...>>>;
    };

    /// Turn a class template or alias template \p F taking literals of
    /// type \p T into a Metafunction Class.
    template <typename T, template <T...> class F> struct quote_i
    {
       private:
        template <typename, typename = quote_i, typename = void> struct impl
        {
        };
        template <typename... Ts, typename U, template <U...> class D>
        struct impl<list<Ts...>, quote_i<U, D>, void_<D<Ts::type::value...>>>
        {
            using type = D<Ts::type::value...>;
        };

       public:
        // Indirection here needed to avoid Core issue 1430
        // http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430
        template <typename... Ts> using apply = eval<impl<list<Ts...>>>;
    };

    /// Turn a metafunction \p C into a Metafunction Class.
    template <template <typename...> class C> struct quote_trait
    {
        template <typename... Ts> using apply = eval<apply<quote<C>, Ts...>>;
    };

    /// Turn a metafunction \p C taking literals of type \p T into a
    /// Metafunction Class.
    template <typename T, template <T...> class C> struct quote_trait_i
    {
        template <typename... Ts>
        using apply = eval<apply<quote_i<T, C>, Ts...>>;
    };

    /// Compose the Metafunction Classes \p Fs in the parameter pack
    /// \p Ts.
    template <typename... Fs> struct compose
    {
    };

    template <typename F0> struct compose<F0>
    {
        template <typename... Ts> using apply = apply<F0, Ts...>;
    };

    template <typename F0, typename... Fs> struct compose<F0, Fs...>
    {
        template <typename... Ts>
        using apply = apply<F0, apply<compose<Fs...>, Ts...>>;
    };

    /// A Metafunction Class that partially applies the Metafunction Class \p F
    /// by binding the arguments \p Ts to the \e front of \p F.
    template <typename F, typename... Ts> struct bind_front
    {
        template <typename... Us> using apply = apply<F, Ts..., Us...>;
    };

    /// A Metafunction Class that partially applies the Metafunction Class \p F
    /// by
    /// binding the arguments \p Us to the \e back of \p F.
    template <typename F, typename... Us> struct bind_back
    {
        template <typename... Ts> using apply = apply<F, Ts..., Us...>;
    };

    /// A metafunction that unpacks the types in the type list \p List into the
    /// Metafunction Class \p F.
    template <typename F, typename List> struct lazy_apply_list
    {
    };

    template <typename F, template <typename...> class T, typename... Ts>
    struct lazy_apply_list<F, T<Ts...>>
    {
        using type = apply<F, Ts...>;
    };

    template <typename F, typename T, T... Is>
    struct lazy_apply_list<F, integer_sequence<T, Is...>>
    {
        using type = apply<F, std::integral_constant<T, Is>...>;
    };

    /// Applies the Metafunction Class \p C using the types in the type list \p
    /// List as arguments.
    template <typename C, typename List>
    using apply_list = eval<lazy_apply_list<C, List>>;

    /// A Metafunction Class that takes a bunch of arguments, bundles them into
    /// a type list, and then calls the Metafunction Class \p F with the type
    /// list \p Q.
    template <typename F, typename Q = quote<list>> using curry = compose<F, Q>;

    /// A Metafunction Class that takes a type list, unpacks the types, and
    /// then calls the Metafunction Class \p F with the types.
    template <typename F> using uncurry = bind_front<quote<apply_list>, F>;

    /// A Metafunction Class that reverses the order of the first two arguments.
    template <typename F> struct flip
    {
       private:
        template <typename... Ts> struct impl
        {
        };
        template <typename A, typename B, typename... Ts>
        struct impl<A, B, Ts...> : lazy_apply<F, B, A, Ts...>
        {
        };

       public:
        template <typename... Ts> using apply = eval<impl<Ts...>>;
    };

    ////////////////////////////////////////////////////////////////////////
    // if_
    /// \cond
    namespace detail
    {
        template <bool If, typename Then, typename Else> struct _if_
        {
            using type = Else;
        };

        template <typename Then, typename Else> struct _if_<true, Then, Else>
        {
            using type = Then;
        };
    } // namespace detail
    /// \endcond

    /// Select one type or another depending on a compile-time Boolean.
    template <typename If, typename Then, typename Else>
    using if_ = eval<detail::_if_<If::type::value, Then, Else>>;

    /// Select one type or another depending on a compile-time Boolean.
    template <bool If, typename Then, typename Else>
    using if_c = eval<detail::_if_<If, Then, Else>>;

    /// \cond
    namespace detail
    {
        template <typename... Bools> struct _and_;

        template <> struct _and_<> : std::true_type
        {
        };

        template <typename Bool, typename... Bools>
        struct _and_<Bool, Bools...>
          : if_c<!Bool::type::value, std::false_type, _and_<Bools...>>
        {
        };

        template <typename... Bools> struct _or_;

        template <> struct _or_<> : std::false_type
        {
        };

        template <typename Bool, typename... Bools>
        struct _or_<Bool, Bools...>
          : if_c<Bool::type::value, std::true_type, _or_<Bools...>>
        {
        };
    } // namespace detail
    /// \endcond

    /// Logically negate the Boolean parameter
    template <bool Bool> using not_c = bool_<!Bool>;

    /// Logically negate the integral constant-wrapped Boolean
    /// parameter.
    template <typename Bool> using not_ = not_c<Bool::type::value>;

    /// Logically and together all the Boolean parameters
    template <bool... Bools>
    using and_c = std::is_same<integer_sequence<bool, Bools...>,
                               integer_sequence<bool, (Bools || true)...>>;

    /// Logically and together all the integral constant-wrapped Boolean
    /// parameters, \e without doing short-circuiting.
    template <typename... Bools> using fast_and = and_c<Bools::type::value...>;

    /// Logically and together all the integral constant-wrapped Boolean
    /// parameters, \e with short-circuiting.
    template <typename... Bools> using and_ = eval<detail::_and_<Bools...>>;

    /// Logically or together all the Boolean parameters
    template <bool... Bools>
    using or_c =
      not_<std::is_same<integer_sequence<bool, Bools...>,
                        integer_sequence<bool, (Bools && false)...>>>;

    /// Logically or together all the integral constant-wrapped Boolean
    /// parameters, \e without doing short-circuiting.
    template <typename... Bools> using fast_or = or_c<Bools::type::value...>;

    /// Logically or together all the integral constant-wrapped Boolean
    /// parameters, \e with short-circuiting.
    template <typename... Bools> using or_ = eval<detail::_or_<Bools...>>;

    ////////////////////////////////////////////////////////////////////////
    // list
    /// A list of types.
    template <typename... Ts> struct list
    {
        using type = list;
        /// \return `sizeof...(Ts)`
        static constexpr std::size_t size() noexcept { return sizeof...(Ts); }
    };

    ////////////////////////////////////////////////////////////////////////
    // size
    /// An integral constant wrapper that is the size of the \c meta::list \p
    /// List.
    template <typename List> using size = meta::size_t<List::size()>;

    ////////////////////////////////////////////////////////////////////////
    // concat
    /// \cond
    namespace detail
    {
        template <typename... Lists> struct concat_
        {
        };

        template <> struct concat_<>
        {
            using type = list<>;
        };

        template <typename... List1> struct concat_<list<List1...>>
        {
            using type = list<List1...>;
        };

        template <typename... List1, typename... List2>
        struct concat_<list<List1...>, list<List2...>>
        {
            using type = list<List1..., List2...>;
        };

        template <typename... List1, typename... List2, typename... List3>
        struct concat_<list<List1...>, list<List2...>, list<List3...>>
        {
            using type = list<List1..., List2..., List3...>;
        };

        template <typename... List1, typename... List2, typename... List3,
                  typename... Rest>
        struct concat_<list<List1...>, list<List2...>, list<List3...>, Rest...>
          : concat_<list<List1..., List2..., List3...>, Rest...>
        {
        };
    } // namespace detail
    /// \endcond

    /// Concatenates several lists into a single list.
    /// \pre The parameters must all be instantiations of \c meta::list.
    /// \par Complexity
    /// \f$ O(L) \f$ where \f$ L \f$ is the number of lists in the list of
    /// lists.
    template <typename... Lists> using concat = eval<detail::concat_<Lists...>>;

    /// Joins a list of lists into a single list.
    /// \pre The parameter must be an instantiation of \c meta::list\<T...\>
    ///      where each \c T is itself an instantiation of \c meta::list.
    /// \par Complexity
    /// \f$ O(L) \f$ where \f$ L \f$ is the number of lists in the list of
    /// lists.
    template <typename ListOfLists>
    using join = apply_list<quote<concat>, ListOfLists>;

    ////////////////////////////////////////////////////////////////////////
    // repeat_n
    /// \cond
    namespace detail
    {
        template <std::size_t N, typename T> struct repeat_n_c_
        {
            using type =
              concat<eval<repeat_n_c_<N / 2, T>>, eval<repeat_n_c_<N / 2, T>>,
                     eval<repeat_n_c_<N % 2, T>>>;
        };

        template <typename T> struct repeat_n_c_<0, T>
        {
            using type = list<>;
        };

        template <typename T> struct repeat_n_c_<1, T>
        {
            using type = list<T>;
        };
    } // namespace detail
    /// \endcond

    /// Generate `list<T,T,T...T>` of size \p N arguments.
    /// \par Complexity
    /// \f$ O(log N) \f$
    template <typename N, typename T = void>
    using repeat_n = eval<detail::repeat_n_c_<N::type::value, T>>;

    /// Generate `list<T,T,T...T>` of size \p N arguments.
    /// \par Complexity
    /// \f$ O(log N) \f$
    template <std::size_t N, typename T = void>
    using repeat_n_c = eval<detail::repeat_n_c_<N, T>>;

    ////////////////////////////////////////////////////////////////////////
    // list_element
    /// \cond
    namespace detail
    {
        template <typename VoidPtrs> struct list_element_impl_;

        template <typename... VoidPtrs>
        struct list_element_impl_<list<VoidPtrs...>>
        {
            static nil_ eval(...);

            template <typename T, typename... Us>
            static T eval(VoidPtrs..., T *, Us *...);
        };

        template <typename N, typename List> struct list_element_
        {
        };

        template <typename N, typename... Ts>
        struct list_element_<N, list<Ts...>>
          : decltype(list_element_impl_<repeat_n<N, void *>>::eval(
              detail::_nullptr_v<id<Ts>>()...))
        {
        };
    } // namespace detail
    /// \endcond

    ////////////////////////////////////////////////////////////////////////
    // list_element
    /// Return the \p N th element in the \c meta::list \p List.
    /// \par Complexity
    /// Amortized \f$ O(1) \f$
    template <typename N, typename List>
    using list_element = eval<detail::list_element_<N, List>>;

    /// Return the \p N th element in the \c meta::list \p List.
    /// \par Complexity
    /// Amortized \f$ O(1) \f$
    template <std::size_t N, typename List>
    using list_element_c = list_element<meta::size_t<N>, List>;

    ////////////////////////////////////////////////////////////////////////
    // drop
    /// \cond
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////
        /// drop_impl_
        template <typename VoidPtrs> struct drop_impl_
        {
            static nil_ eval(...);
        };

        template <typename... VoidPtrs> struct drop_impl_<list<VoidPtrs...>>
        {
            static nil_ eval(...);

            template <typename... Ts>
            static id<list<Ts...>> eval(VoidPtrs..., id<Ts> *...);
        };

        template <typename N, typename List> struct drop_
        {
        };

        template <typename N, typename... Ts>
        struct drop_<N, list<Ts...>>
          : decltype(drop_impl_<repeat_n<N, void *>>::eval(
              detail::_nullptr_v<id<Ts>>()...))
        {
        };
    } // namespace detail
    /// \endcond

    /// Return a new \c meta::list by removing the first \p N elements from \p
    /// List.
    /// \par Complexity
    /// \f$ O(1) \f$
    template <typename N, typename List>
    using drop = eval<detail::drop_<N, List>>;

    /// Return a new \c meta::list by removing the first \p N elements from \p
    /// List.
    /// \par Complexity
    /// \f$ O(1) \f$
    template <std::size_t N, typename List>
    using drop_c = eval<detail::drop_<meta::size_t<N>, List>>;

    ////////////////////////////////////////////////////////////////////////
    // front
    /// \cond
    namespace detail
    {
        template <typename List> struct front_
        {
        };

        template <typename Head, typename... List>
        struct front_<list<Head, List...>>
        {
            using type = Head;
        };
    } // namespace detail
    /// \endcond

    /// Return the first element in \c meta::list \p List.
    /// \par Complexity
    /// \f$ O(1) \f$
    template <typename List> using front = eval<detail::front_<List>>;

    ////////////////////////////////////////////////////////////////////////
    // back
    /// \cond
    namespace detail
    {
        template <typename List> struct back_
        {
        };

        template <typename Head, typename... List>
        struct back_<list<Head, List...>>
        {
            using type = list_element_c<sizeof...(List), list<Head, List...>>;
        };
    } // namespace detail
    /// \endcond

    /// Return the last element in \c meta::list \p List.
    /// \par Complexity
    /// Amortized \f$ O(1) \f$.
    template <typename List> using back = eval<detail::back_<List>>;

    ////////////////////////////////////////////////////////////////////////
    // push_front
    /// \cond
    namespace detail
    {
        template <typename List, typename T> struct push_front_
        {
        };

        template <typename... List, typename T>
        struct push_front_<list<List...>, T>
        {
            using type = list<T, List...>;
        };
    } // namespace detail
    /// \endcond

    /// Return a new \c meta::list by adding the element \c T to the front of \p
    /// List.
    /// \par Complexity
    /// \f$ O(1) \f$.
    template <typename List, typename T>
    using push_front = eval<detail::push_front_<List, T>>;

    ////////////////////////////////////////////////////////////////////////
    // pop_front
    /// \cond
    namespace detail
    {
        template <typename List> struct pop_front_
        {
        };

        template <typename Head, typename... List>
        struct pop_front_<list<Head, List...>>
        {
            using type = list<List...>;
        };
    } // namespace detail
    /// \endcond

    /// Return a new \c meta::list by removing the first element from the front
    /// of \p List.
    /// \par Complexity
    /// \f$ O(1) \f$.
    template <typename List> using pop_front = eval<detail::pop_front_<List>>;

    ////////////////////////////////////////////////////////////////////////
    // push_back
    /// \cond
    namespace detail
    {
        template <typename List, typename T> struct push_back_
        {
        };

        template <typename... List, typename T>
        struct push_back_<list<List...>, T>
        {
            using type = list<List..., T>;
        };
    } // namespace detail
    /// \endcond

    /// Return a new \c meta::list by adding the element \c T to the back of \p
    /// List.
    /// \par Complexity
    /// \f$ O(1) \f$.
    /// \note pop_back not provided because it cannot be made to meet the
    /// complexity guarantees one would expect.
    template <typename List, typename T>
    using push_back = eval<detail::push_back_<List, T>>;

    ////////////////////////////////////////////////////////////////////////
    // empty
    /// An Boolean integral constant wrapper around \c true if \p List is an
    /// empty type list; \c false, otherwise.
    template <typename List> using empty = bool_<0 == size<List>::type::value>;

    ////////////////////////////////////////////////////////////////////////
    // find
    /// \cond
    namespace detail
    {
        template <typename List, typename T> struct find_
        {
        };

        template <typename T> struct find_<list<>, T>
        {
            using type = list<>;
        };

        template <typename Head, typename... List, typename T>
        struct find_<list<Head, List...>, T> : find_<list<List...>, T>
        {
        };

        template <typename... List, typename T>
        struct find_<list<T, List...>, T>
        {
            using type = list<T, List...>;
        };
    } // namespace detail
    /// \endcond

    /// Return the tail of the list \p List starting at the first occurrence of
    /// \c T, if any such element exists; the empty list, otherwise.
    template <typename List, typename T>
    using find = eval<detail::find_<List, T>>;

    ////////////////////////////////////////////////////////////////////////
    // find_if
    /// \cond
    namespace detail
    {
        template <typename List, typename Fun> struct find_if_
        {
        };

        template <typename Fun> struct find_if_<list<>, Fun>
        {
            using type = list<>;
        };

        template <typename Head, typename... List, typename Fun>
        struct find_if_<list<Head, List...>, Fun>
          : if_<apply<Fun, Head>, id<list<Head, List...>>,
                find_if_<list<List...>, Fun>>
        {
        };
    } // namespace detail
    /// \endcond

    /// Return the tail of the list \p List starting at the first element `A`
    /// such that `apply<Fun, A>::%value` is \c true, if any such element
    /// exists; the empty list, otherwise.
    template <typename List, typename Fun>
    using find_if = eval<detail::find_if_<List, Fun>>;

    ////////////////////////////////////////////////////////////////////////
    // in
    /// A Boolean integral constant wrapper around \c true if there is at least
    /// one occurrence of `T` in \p List.
    template <typename List, typename T> using in = not_<empty<find<List, T>>>;

    ////////////////////////////////////////////////////////////////////////
    // unique
    /// \cond
    namespace detail
    {
        template <typename List, typename Result> struct unique_
        {
        };

        template <typename Result> struct unique_<list<>, Result>
        {
            using type = Result;
        };

        template <typename Head, typename... List, typename Result>
        struct unique_<list<Head, List...>, Result>
          : unique_<list<List...>, apply<if_<in<Result, Head>, quote_trait<id>,
                                             bind_back<quote<push_back>, Head>>,
                                         Result>>
        {
        };
    } // namespace detail
    /// \endcond

    /// Return a new \c meta::list where all duplicate elements have been
    /// removed.
    /// \par Complexity
    /// \f$ O(N^2) \f$.
    template <typename List> using unique = eval<detail::unique_<List, list<>>>;

    ////////////////////////////////////////////////////////////////////////
    // replace
    /// \cond
    namespace detail
    {
        template <typename List, typename T, typename U> struct replace_
        {
        };

        template <typename... List, typename T, typename U>
        struct replace_<list<List...>, T, U>
        {
            using type = list<if_<std::is_same<T, List>, U, List>...>;
        };
    } // namespace detail
    /// \endcond

    /// Return a new \c meta::list where all instances of type \c T have been
    /// replaced with \c U.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename T, typename U>
    using replace = eval<detail::replace_<List, T, U>>;

    ////////////////////////////////////////////////////////////////////////
    // replace_if
    /// \cond
    namespace detail
    {
        template <typename List, typename C, typename U> struct replace_if_
        {
        };

        template <typename... List, typename C, typename U>
        struct replace_if_<list<List...>, C, U>
        {
            using type = list<if_<apply<C, List>, U, List>...>;
        };
    } // namespace detail
    /// \endcond

    /// Return a new \c meta::list where all elements \c A such that `apply<C,
    /// A>::%value` is \c true have been replaced with \c U.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename C, typename U>
    using replace_if = eval<detail::replace_if_<List, C, U>>;

    ////////////////////////////////////////////////////////////////////////
    // foldl
    /// \cond
    namespace detail
    {
        template <typename, typename, typename, typename = void> struct foldl_
        {
        };

        template <typename State, typename Fun>
        struct foldl_<list<>, State, Fun>
        {
            using type = State;
        };

        template <typename Head, typename... List, typename State, typename Fun>
        struct foldl_<list<Head, List...>, State, Fun,
                      void_<apply<Fun, State, Head>>>
          : foldl_<list<List...>, apply<Fun, State, Head>, Fun>
        {
        };
    } // namespace detail
    /// \endcond

    /// Return a new \c meta::list constructed by doing a left fold of the list
    /// \p List using binary Metafunction Class \c Fun and initial state \c
    /// State.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename State, typename Fun>
    using foldl = eval<detail::foldl_<List, State, Fun>>;

    /// An alias for `meta::foldl`.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename State, typename Fun>
    using accumulate = foldl<List, State, Fun>;

    ////////////////////////////////////////////////////////////////////////
    // foldr
    /// \cond
    namespace detail
    {
        template <typename, typename, typename, typename = void> struct foldr_
        {
        };

        template <typename State, typename Fun>
        struct foldr_<list<>, State, Fun>
        {
            using type = State;
        };

        template <typename Head, typename... List, typename State, typename Fun>
        struct foldr_<list<Head, List...>, State, Fun,
                      void_<eval<foldr_<list<List...>, State, Fun>>>>
          : lazy_apply<Fun, eval<foldr_<list<List...>, State, Fun>>, Head>
        {
        };
    } // namespace detail
    /// \endcond

    /// Return a new \c meta::list constructed by doing a right fold of the list
    /// \p List using binary Metafunction Class \c Fun and initial state \c
    /// State.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename State, typename Fun>
    using foldr = eval<detail::foldr_<List, State, Fun>>;

    ////////////////////////////////////////////////////////////////////////
    // transform
    /// \cond
    namespace detail
    {
        template <typename, typename, typename = void> struct transform1_
        {
        };

        template <typename... List, typename Fun>
        struct transform1_<list<List...>, Fun, void_<list<apply<Fun, List>...>>>
        {
            using type = list<apply<Fun, List>...>;
        };

        template <typename, typename, typename, typename = void>
        struct transform2_
        {
        };

        template <typename... List0, typename... List1, typename Fun>
        struct transform2_<list<List0...>, list<List1...>, Fun,
                           void_<list<apply<Fun, List0, List1>...>>>
        {
            using type = list<apply<Fun, List0, List1>...>;
        };

        template <typename... Args> struct transform_
        {
        };

        template <typename List, typename Fun>
        struct transform_<List, Fun> : transform1_<List, Fun>
        {
        };

        template <typename List0, typename List1, typename Fun>
        struct transform_<List0, List1, Fun> : transform2_<List0, List1, Fun>
        {
        };
    } // namespace detail
    /// \endcond

    /// Return a new \c meta::list constructed by transforming all the elements
    /// in \p List with the unary Metafuncion Class Fun. \c transform can also
    /// be called with two lists of the same length and a binary Metafunction
    /// Class, in which case it returns a new list constructed with the results
    /// of calling \c Fun with each element in the lists, pairwise.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename... Args>
    using transform = eval<detail::transform_<Args...>>;

    ////////////////////////////////////////////////////////////////////////
    // zip_with
    /// Given a list of lists of types and a Metafunction Class \c Fun,
    /// construct a new list by calling \c Fun with the elements from the lists
    /// pairwise.
    /// \par Complexity
    /// \f$ O(N*M) \f$, where \f$ N \f$ is the size of the outer list, and
    /// \f$ M \f$ is the size of the inner lists.
    template <typename Fun, typename ListOfLists>
    using zip_with =
      transform<foldl<ListOfLists, repeat_n<size<front<ListOfLists>>, Fun>,
                      bind_back<quote<transform>, quote<bind_front>>>,
                quote<apply>>;

    ////////////////////////////////////////////////////////////////////////
    // zip
    /// Given a list of lists of types, construct a new list by grouping the
    /// elements from the lists pairwise into `meta::list`s.
    /// \par Complexity
    /// \f$ O(N*M) \f$, where \f$ N \f$ is the size of the outer list, and
    /// \f$ M \f$ is the size of the inner lists.
    template <typename ListOfLists>
    using zip = zip_with<quote<list>, ListOfLists>;

    ////////////////////////////////////////////////////////////////////////
    // as_list
    /// \cond
    namespace detail
    {
        template <typename T>
        using uncvref_t = eval<std::remove_cv<eval<std::remove_reference<T>>>>;

        // Indirection here needed to avoid Core issue 1430
        // http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430
        template <typename Sequence>
        struct as_list_
          : lazy_apply<uncurry<curry<quote_trait<id>>>, uncvref_t<Sequence>>
        {
        };
    } // namespace detail
    /// \endcond

    /// Turn a type into an instance of \c meta::list in a way determined by \c
    /// meta::lazy_apply_list.
    template <typename Sequence>
    using as_list = eval<detail::as_list_<Sequence>>;

    ////////////////////////////////////////////////////////////////////////
    // reverse
    /// Return a new \c meta::list by reversing the elements in the list \p
    /// List.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List>
    using reverse = foldr<List, list<>, quote<push_back>>;

    ////////////////////////////////////////////////////////////////////////
    // all_of
    /// A Boolean integral constant wrapper around \c true if `apply<F,
    /// A>::%value` is \c true for all elements \c A in \c meta::list \p List;
    /// \c false, otherwise.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename F>
    using all_of = empty<find_if<List, compose<quote<not_>, F>>>;

    ////////////////////////////////////////////////////////////////////////
    // any_of
    /// A Boolean integral constant wrapper around \c true if `apply<F,
    /// A>::%value` is \c true for any element \c A in \c meta::list \p List; \c
    /// false, otherwise.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename F>
    using any_of = not_<empty<find_if<List, F>>>;

    ////////////////////////////////////////////////////////////////////////
    // none_of
    /// A Boolean integral constant wrapper around \c true if `apply<F,
    /// A>::%value` is \c false for alls elements \c A in \c meta::list \p List;
    /// \c false, otherwise.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename F>
    using none_of = empty<find_if<List, F>>;

    ////////////////////////////////////////////////////////////////////////
    // cartesian_product
    /// \cond
    namespace detail
    {
        template <typename M2, typename M> struct cartesian_product_fn
        {
            template <typename X> struct lambda0
            {
                template <typename Xs> using lambda1 = list<push_front<Xs, X>>;
                using type = join<transform<M2, quote<lambda1>>>;
            };
            using type = join<transform<M, quote_trait<lambda0>>>;
        };
    } // namespace detail
    /// \endcond

    /// Given a list of lists, return a new list of lists that is the Cartesian
    /// Product. Like the `sequence` function from the Haskell Prelude.
    /// \par Complexity
    /// \f$ O(N * M) \f$.
    template <typename ListOfLists>
    using cartesian_product = foldr<ListOfLists, list<list<>>,
                                    quote_trait<detail::cartesian_product_fn>>;

    /// \cond
    ////////////////////////////////////////////////////////////////////////
    // add_const_if
    template <typename If>
    using add_const_if = if_<If, quote_trait<std::add_const>, quote_trait<id>>;

    template <bool If>
    using add_const_if_c =
      if_c<If, quote_trait<std::add_const>, quote_trait<id>>;
    /// \endcond

    ////////////////////////////////////////////////////////////////////////
    // Math operations
    /// An integral constant wrapper around the result of adding the two wrapped
    /// integers \c T::type::value and \c U::type::value.
    template <typename T, typename U>
    using plus =
      std::integral_constant<decltype(T::type::value + U::type::value),
                             T::type::value + U::type::value>;

    /// An integral constant wrapper around the result of subtracting the two
    /// wrapped integers \c T::type::value and \c U::type::value.
    template <typename T, typename U>
    using minus =
      std::integral_constant<decltype(T::type::value - U::type::value),
                             T::type::value - U::type::value>;

    /// An integral constant wrapper around the result of multiplying the two
    /// wrapped integers \c T::type::value and \c U::type::value.
    template <typename T, typename U>
    using multiplies =
      std::integral_constant<decltype(T::type::value *U::type::value),
                             T::type::value * U::type::value>;

    /// An integral constant wrapper around the result of dividing the two
    /// wrapped integers \c T::type::value and \c U::type::value.
    template <typename T, typename U>
    using divides =
      std::integral_constant<decltype(T::type::value / U::type::value),
                             T::type::value / U::type::value>;

    /// An integral constant wrapper around the remainder of dividing the two
    /// wrapped integers \c T::type::value and \c U::type::value.
    template <typename T>
    using negate =
      std::integral_constant<decltype(-T::type::value), -T::type::value>;

    /// An integral constant wrapper around the remainder of dividing the two
    /// wrapped integers \c T::type::value and \c U::type::value.
    template <typename T, typename U>
    using modulus =
      std::integral_constant<decltype(T::type::value % U::type::value),
                             T::type::value % U::type::value>;

    /// A Boolean integral constant wrapper around the result of comparing \c
    /// T::type::value and \c U::type::value for equality.
    template <typename T, typename U>
    using equal_to = bool_<T::type::value == U::type::value>;

    /// A Boolean integral constant wrapper around the result of comparing \c
    /// T::type::value and \c U::type::value for inequality.
    template <typename T, typename U>
    using not_equal_to = bool_<T::type::value != U::type::value>;

    /// A Boolean integral constant wrapper around \c true if \c T::type::value
    /// is greater than \c U::type::value; \c false, otherwise.
    template <typename T, typename U>
    using greater = bool_<(T::type::value > U::type::value)>;

    /// A Boolean integral constant wrapper around \c true if \c T::type::value
    /// is less than \c U::type::value; \c false, otherwise.
    template <typename T, typename U>
    using less = bool_<(T::type::value < U::type::value)>;

    /// A Boolean integral constant wrapper around \c true if \c T::type::value
    /// is greater than or equal to \c U::type::value; \c false, otherwise.
    template <typename T, typename U>
    using greater_equal = bool_<(T::type::value >= U::type::value)>;

    /// A Boolean integral constant wrapper around \c true if \c T::type::value
    /// is less than or equal to \c U::type::value; \c false, otherwise.
    template <typename T, typename U>
    using less_equal = bool_<(T::type::value <= U::type::value)>;

    /// An integral constant wrapper around the result of bitwise-and'ing the
    /// two wrapped integers \c T::type::value and \c U::type::value.
    template <typename T, typename U>
    using bit_and =
      std::integral_constant<decltype(T::type::value &U::type::value),
                             T::type::value & U::type::value>;

    /// An integral constant wrapper around the result of bitwise-or'ing the two
    /// wrapped integers \c T::type::value and \c U::type::value.
    template <typename T, typename U>
    using bit_or =
      std::integral_constant<decltype(T::type::value | U::type::value),
                             T::type::value | U::type::value>;

    /// An integral constant wrapper around the result of
    /// bitwise-exclusive-or'ing the two wrapped integers \c T::type::value and
    /// \c U::type::value.
    template <typename T, typename U>
    using bit_xor =
      std::integral_constant<decltype(T::type::value ^ U::type::value),
                             T::type::value ^ U::type::value>;

    /// An integral constant wrapper around the result of bitwise-complimenting
    /// the wrapped integer \c T::type::value.
    template <typename T>
    using bit_not =
      std::integral_constant<decltype(~T::type::value), ~T::type::value>;

    ////////////////////////////////////////////////////////////////////////////
    // integer_sequence

    /// A container for a sequence of compile-time integer constants.
    template <typename T, T... Is> struct integer_sequence
    {
        using value_type = T;
        /// \return `sizeof...(Is)`
        static constexpr std::size_t size() noexcept { return sizeof...(Is); }
    };

    /// \cond
    namespace detail
    {
        
        // Glue two sets of integer_sequence together
        template <typename... T>
        struct integer_sequence_cat;

        template <typename T, T... N1, T... N2, T... N3>
        struct integer_sequence_cat<    integer_sequence<T, N1...>,
                                        integer_sequence<T, N2...>,
                                        integer_sequence<T, N3...>>
        {
            using type =
              integer_sequence<T, N1..., N2..., N3...>;
        };

        
        
        template <typename T, T S, T N, typename = std::integral_constant<T,N> >
        struct make_integer_sequence_
          : integer_sequence_cat<meta::eval<make_integer_sequence_<T, S          , N/2>>,
                                 meta::eval<make_integer_sequence_<T, S + N/2    , N/2>>,
                                 meta::eval<make_integer_sequence_<T, S + 2*(N/2), N%2>>>
        {
        };

        template <typename T, T S, T N> struct make_integer_sequence_<T, S, N,  std::integral_constant<T,0> >
        {
            using type = integer_sequence<T>;
        };

        template <typename T, T S, T N> struct make_integer_sequence_<T, S, N, std::integral_constant<T,1> >
        {
            using type = integer_sequence<T, S>;
        };
        
        
        
        
    } // namespace detail
    /// \endcond

    /// Generate \c integer_sequence containing integer constants
    /// [S,...,E-1]
    /// \par Complexity
    /// \f$ O(log(N)) \f$.
    template <typename T, T S, T E>
    using make_integer_sequence = 
        meta::eval< detail::make_integer_sequence_<T, S, (E<=S)? 0 : E-S > >;
    
    /// A container for a sequence of compile-time integer constants of type \c
    /// std::size_t
    template <std::size_t... Is>
    using index_sequence = integer_sequence<std::size_t, Is...>;

    /// Generate \c index_sequence containing integer constants [0,1,2,...,N-1].
    /// \par Complexity
    /// \f$ O(log(N)) \f$.
    template <std::size_t E>
    using make_index_sequence = make_integer_sequence<std::size_t, 0, E>;


    template <std::size_t S, std::size_t E>
    using make_index_range = make_integer_sequence<std::size_t, S, E>;
    

    ///@}  // group meta
} // namespace meta

/// \file meta_libcxx_workaround.hpp Make meta::quote work consistently with
/// libc++ containers
///
/// Works around: http://llvm.org/bugs/show_bug.cgi?id=22601
///  and http://llvm.org/bugs/show_bug.cgi?id=22605 Meta library
//
//  Copyright Eric Niebler 2014-2015
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/meta
//
#ifndef META_HPP_LIBCXX_WORKAROUND
#define META_HPP_LIBCXX_WORKAROUND

#if defined(__clang__) && defined(_LIBCPP_VERSION) && _LIBCPP_VERSION <= 1101

_LIBCPP_BEGIN_NAMESPACE_STD
template <class> class _LIBCPP_TYPE_VIS_ONLY allocator;
template <class, class> struct _LIBCPP_TYPE_VIS_ONLY pair;
template <class> struct _LIBCPP_TYPE_VIS_ONLY hash;
template <class> struct _LIBCPP_TYPE_VIS_ONLY less;
template <class> struct _LIBCPP_TYPE_VIS_ONLY equal_to;
template <class> struct _LIBCPP_TYPE_VIS_ONLY char_traits;
template <class, class> class _LIBCPP_TYPE_VIS_ONLY list;
template <class, class> class _LIBCPP_TYPE_VIS_ONLY forward_list;
template <class, class> class _LIBCPP_TYPE_VIS_ONLY vector;
template <class, class> class _LIBCPP_TYPE_VIS_ONLY deque;
template <class, class, class> class _LIBCPP_TYPE_VIS_ONLY basic_string;
template <class, class, class, class> class _LIBCPP_TYPE_VIS_ONLY map;
template <class, class, class, class> class _LIBCPP_TYPE_VIS_ONLY multimap;
template <class, class, class> class _LIBCPP_TYPE_VIS_ONLY set;
template <class, class, class> class _LIBCPP_TYPE_VIS_ONLY multiset;
template <class, class, class, class, class>
class _LIBCPP_TYPE_VIS_ONLY unordered_map;
template <class, class, class, class, class>
class _LIBCPP_TYPE_VIS_ONLY unordered_multimap;
template <class, class, class, class> class _LIBCPP_TYPE_VIS_ONLY unordered_set;
template <class, class, class, class>
class _LIBCPP_TYPE_VIS_ONLY unordered_multiset;
template <class, class> class _LIBCPP_TYPE_VIS_ONLY queue;
template <class, class, class> class _LIBCPP_TYPE_VIS_ONLY priority_queue;
template <class, class> class _LIBCPP_TYPE_VIS_ONLY stack;
_LIBCPP_END_NAMESPACE_STD

namespace meta
{
    namespace detail
    {
        template <typename T, typename A = std::allocator<T>>
        using std_list = std::list<T, A>;
        template <typename T, typename A = std::allocator<T>>
        using std_forward_list = std::forward_list<T, A>;
        template <typename T, typename A = std::allocator<T>>
        using std_vector = std::vector<T, A>;
        template <typename T, typename A = std::allocator<T>>
        using std_deque = std::deque<T, A>;
        template <typename T, typename C = std::char_traits<T>,
                  typename A = std::allocator<T>>
        using std_basic_string = std::basic_string<T, C, A>;
        template <typename K, typename V, typename C = std::less<K>,
                  typename A = std::allocator<std::pair<K const, V>>>
        using std_map = std::map<K, V, C, A>;
        template <typename K, typename V, typename C = std::less<K>,
                  typename A = std::allocator<std::pair<K const, V>>>
        using std_multimap = std::multimap<K, V, C, A>;
        template <typename K, typename C = std::less<K>,
                  typename A = std::allocator<K>>
        using std_set = std::set<K, C, A>;
        template <typename K, typename C = std::less<K>,
                  typename A = std::allocator<K>>
        using std_multiset = std::multiset<K, C, A>;
        template <typename K, typename V, typename H = std::hash<K>,
                  typename C = std::equal_to<K>,
                  typename A = std::allocator<std::pair<K const, V>>>
        using std_unordered_map = std::unordered_map<K, V, H, C, A>;
        template <typename K, typename V, typename H = std::hash<K>,
                  typename C = std::equal_to<K>,
                  typename A = std::allocator<std::pair<K const, V>>>
        using std_unordered_multimap = std::unordered_multimap<K, V, H, C, A>;
        template <typename K, typename H = std::hash<K>,
                  typename C = std::equal_to<K>, typename A = std::allocator<K>>
        using std_unordered_set = std::unordered_set<K, H, C, A>;
        template <typename K, typename H = std::hash<K>,
                  typename C = std::equal_to<K>, typename A = std::allocator<K>>
        using std_unordered_multiset = std::unordered_multiset<K, H, C, A>;
        template <typename T, typename C = std_deque<T>>
        using std_queue = std::queue<T, C>;
        template <typename T, typename C = std_vector<T>,
                  class D = std::less<typename C::value_type>>
        using std_priority_queue = std::priority_queue<T, C, D>;
        template <typename T, typename C = std_deque<T>>
        using std_stack = std::stack<T, C>;
    }

    template <> struct quote< ::std::list > : quote<detail::std_list>
    {
    };
    template <> struct quote< ::std::deque > : quote<detail::std_deque>
    {
    };
    template <>
    struct quote< ::std::forward_list > : quote<detail::std_forward_list>
    {
    };
    template <> struct quote< ::std::vector > : quote<detail::std_vector>
    {
    };
    template <>
    struct quote< ::std::basic_string > : quote<detail::std_basic_string>
    {
    };
    template <> struct quote< ::std::map > : quote<detail::std_map>
    {
    };
    template <> struct quote< ::std::multimap > : quote<detail::std_multimap>
    {
    };
    template <> struct quote< ::std::set > : quote<detail::std_set>
    {
    };
    template <> struct quote< ::std::multiset > : quote<detail::std_multiset>
    {
    };
    template <>
    struct quote< ::std::unordered_map > : quote<detaifl::std_unordered_map>
    {
    };
    template <>
    struct quote< ::std::unordered_multimap >
      : quote<detail::std_unordered_multimap>
    {
    };
    template <>
    struct quote< ::std::unordered_set > : quote<detail::std_unordered_set>
    {
    };
    template <>
    struct quote< ::std::unordered_multiset >
      : quote<detail::std_unordered_multiset>
    {
    };
    template <> struct quote< ::std::queue > : quote<detail::std_queue>
    {
    };
    template <>
    struct quote< ::std::priority_queue > : quote<detail::std_priority_queue>
    {
    };
    template <> struct quote< ::std::stack > : quote<detail::std_stack>
    {
    };
}

#endif

#endif

#endif


// Compile time index calculations for symmetric matrices where the upper part is stored linearly
namespace details{
    
    template<typename T, T N, T R, T C, T L, typename = std::integral_constant <T, L>  >
    struct toRowColSym_impl{
        
        static_assert(L < N*N, "linear offset needs to be smaller or equal max index N*N-1");
        
        using res =         typename std::conditional< (L >= N) ,  
                                               toRowColSym_impl<T, N-1,R+1,C+1,L-N>,
                                               toRowColSym_impl<T, N,R,C+L,0>
                                             >::type;
        static const T i = res::i;
        static const T j = res::j;
    
    };
    
    template<typename T, T N, T R, T C, T L>
    struct toRowColSym_impl<T, N, R, C, L, std::integral_constant <T,0> >
    {
        static const T i = R;
        static const T j = C;
    };
    
    
    template<typename T, T R, T C, T N>
    struct toLinearIdxSym_impl
    {   
        // Switch indices if R,C in lower part of matrix
        static_assert(R < N && C < N, "row and col smaller then N");
        using type = meta::size_t< (R<=C)?            R*N + C - R*(R+1)/2     :         C*N + R - C*(C+1)/2 >;
    };
}

/** Get the row and column of the linear index \p L of the upper part of a symetric matrix of size \p N */
template<std::size_t L, std::size_t N>
using toRowColSym_c = typename details::toRowColSym_impl<std::size_t, N,0,0,L>; 
template<typename L, typename N>
using toRowColSym = typename details::toRowColSym_impl<std::size_t, N::type::value ,0,0,L::type::value>;

/** Get the linear index of the element at row \p R and col \p C of the linear stored upper part of a symetric matrix of size \p N  */
template<std::size_t R, std::size_t C, std::size_t N>
using toLinearIdxSym_c = details::toLinearIdxSym_impl<std::size_t,R,C,N>;
template<typename R, typename C, typename N>
using toLinearIdxSym = details::toLinearIdxSym_impl<std::size_t,R::type::value,C::type::value,N::type::value>;


template<typename TNodeData, typename TEdgeData>
struct CGTraits{
    
    using NodeDataTypes = TNodeData;
    using EdgeDataTypes = TEdgeData;
    static const int nNodes = NodeDataTypes::size();
    static const int nEdges = EdgeDataTypes::size();
    
    static_assert( nNodes*(nNodes-1) == nEdges ,"Number of edges not equal to nodes!");
    
    template<std::size_t R, std::size_t C, std::size_t N>
    using toLinearIdx_c = toLinearIdxSym_c<R,C,N>;
    template<typename R, typename C, typename N>
    using toLinearIdx = toLinearIdxSym<R,C,N>;
    
    // build map , node to all edges
    template<typename I>
    using outEdgesForNode =
            meta::transform<
                meta::as_list<meta::make_index_sequence< nNodes >>,
                meta::compose<
                    meta::bind_back<meta::quote<meta::list_element>,  EdgeDataTypes>,
                    meta::bind_back<meta::bind_front<meta::quote<toLinearIdx>, I >, meta::size_t<nNodes> >
                >
            >;
    
    template<typename J>
    using inEdgesForNode =
            meta::transform<
                meta::as_list<meta::make_index_sequence< nNodes >>,
                meta::compose<
                    meta::bind_back<meta::quote<meta::list_element>,  EdgeDataTypes>,
                    meta::bind_back<meta::quote<toLinearIdx>,  J , meta::size_t<nNodes> >
                >
            >;
    
    /** produces this list   
     * meta::list<
            meta::list<EdgeDataAA, EdgeDataAB, EdgeDataAC>,
            meta::list<EdgeDataAB, EdgeDataBB, EdgeDataBC>,
            meta::list<EdgeDataAC, EdgeDataBC, EdgeDataCC>
        >
    */
    using nodesToEdges = 
        meta::transform<
            meta::as_list<meta::make_index_sequence<nNodes>>,
            meta::quote<edgesForNode>
        >;
    
    // build map, edge to start/end node
    template<typename I>
    using nodesForEdge =
        meta::list<
            meta::list_element<I,EdgeDataTypes>,
            meta::list<
                meta::list_element< meta::size_t< toRowColSym_c<I::value , nNodes>::i> , NodeDataTypes>,
                meta::list_element< meta::size_t< toRowColSym_c<I::value , nNodes>::j> , NodeDataTypes>
            >
        >;
        
    /** produces this list   
    meta::list<
        meta::list<EdgeDataAA, meta::list<NodeDataA, NodeDataA> >,
        meta::list<EdgeDataAB, meta::list<NodeDataA, NodeDataB> >,
        meta::list<EdgeDataAC, meta::list<NodeDataA, NodeDataC> >,
        meta::list<EdgeDataBB, meta::list<NodeDataB, NodeDataB> >,
        meta::list<EdgeDataBC, meta::list<NodeDataB, NodeDataC> >,
        meta::list<EdgeDataCC, meta::list<NodeDataC, NodeDataC> > 
    >*/
    //using edgeToNodes = 
    //    meta::transform<
    //        meta::as_list<meta::make_index_sequence<nEdges>>,
    //        meta::quote<nodesForEdge>
    //    >;
    
    /** Get idx for node */
    template<typename T, typename List>
    struct getIdx{
        static const std::size_t i = meta::find< List, T >::size();
        static_assert( i > 0, "Idx not found!");
        using type = meta::size_t< List::size() - i >;
    };
    
    template<typename TTNodeData>
    using getNodeDataIdx = meta::eval<getIdx<TTNodeData,NodeDataTypes> >;
    
    template<typename TTEdgeData>
    using getEdgeDataIdx = meta::eval<getIdx<TTEdgeData,EdgeDataTypes>>;
    
    
};

struct NodeDataA{};
struct NodeDataB{};
struct NodeDataC{};
struct NodeDataD{}; // Dummy

struct EdgeDataAA{};
struct EdgeDataAB{};
struct EdgeDataAC{};
struct EdgeDataBB{};
struct EdgeDataBC{};
struct EdgeDataCC{};


template<typename TEdgeData, typename TTraits>
class Edge;

template<typename TEdgeData, typename TTraits>
class Node;


template<typename TEdgeData, typename TTraits, bool  >
class Edge{
    public:
    
    using Traits = TTraits;
    
    using EdgeData = meta::list_element< 
                                        Ttraits::template toLinearIdx< 
                                            meta::eval<getIdx<TStartNodeData, typename Traits::NodeDataTypes >> , 
                                            meta::eval<getIdx<TEndNodeData  , typename Traits::NodeDataTypes >> ,
                                            Traits::NodeDataTypes::size()
                                        >, 
                                        EdgeDataTypes
                                        >;
    
                                
    using StartNodeType = TStartNodeData; 
    using EndNodeType   = TEndNodeData; 
    using TwinEdge      = Edge;
    
    StartNodeType * m_startNode;
    EndNodeType * m_endNode;
    
    TwinEdge * m_twinEdge;
    
    EdgeData m_data;
};

template<typename TNodeData, typename TTraits>
class Node{
    public:
    
    using NodeData = TNodeData;
    using Traits = TTraits;
    
    using OutEdgeDataTypes = meta::unique< typename Traits::template outEdgesForNode< typename Traits::template getNodeDataIdx<NodeData> > >
    ;
    // Make a meta::list< std::vector< Edge<...> *> , std::vector< Edge<...> * > , .... >  for all edge types
    
    template<typename List, typename F>
    using makeTupleVectorPtr = meta::transform<  
                                    EdgeDataTypes,
                                    meta::compose< 
                                        meta::quote<std::vector>,
                                        meta::quote<meta::eval>, // add pointer needs to be evaluated ::type
                                        meta::quote<std::add_pointer>,
                                         
                                    >
                                >;
    
    using OutEdgeStoragesTypes = makeTupleVectorPtr< OutEdgeDataTypes, meta::bind_back<meta::quote<Edge>,Traits, meta::bool_<false> > >;
    
    
    using InEdgeDataTypes  = meta::unique< typename Traits::template inEdgesForNode < typename Traits::template getNodeDataIdx<NodeData> > >;
    using InEdgeStoragesTypes = makeTupleVectorPtr< OutEdgeDataTypes, 
                                                    meta::bind_back<meta::quote<Edge>,Traits, meta:if_<typename Traits::edgesAreSymmetric, meta::bool_<true>, meta::bool_<false>> >
                                                  >;
    EdgeStorageType m_edges;
    
    template<typename T>
    void addEdge(T * e){
        using Idx = typename Traits::template getIdx<typename T::EdgeData, EdgeDataTypes>;
        std::get< Idx::type::value >(m_edges).push_back(e);          
    }
    
};


int main()
{
 
   using cg = CGTraits< meta::list<NodeDataA,NodeDataB,NodeDataC>, meta::list<EdgeDataAA,EdgeDataAB,EdgeDataAC,EdgeDataBB,EdgeDataBC,EdgeDataCC> >;
   
   //cg::edgeToNodes;
    std::cout << "idx:" << cg::getNodeDataIdx<NodeDataC>::value << std::endl;
    
    //std::cout << type(Node<NodeDataB,cg>::EdgeDataTypes() ) << std::endl; ;
    
    Node<NodeDataA,cg> a;
    Node<NodeDataB,cg> b;
    Node<NodeDataC,cg> c;
    
    Edge<EdgeDataAB,cg> e_ab;
    e_ab.m_startNode = &a;
    e_ab.m_endNode = &b;
    
    
    Edge<EdgeDataBC,cg> e_bc;
    e_bc.m_startNode = &b;
    e_bc.m_endNode = &c;
    
    a.addEdge(&e_ab);
    b.addEdge(&e_ab);
    
    b.addEdge(&e_bc);
    c.addEdge(&e_bc);
    
    Edge<EdgeDataAC,cg> e_ca;
    e_ca.m_startNode = &c;
    e_ca.m_endNode = &a;
    
    
   return 0;
}
