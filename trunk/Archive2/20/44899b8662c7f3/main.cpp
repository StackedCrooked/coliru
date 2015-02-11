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
    }

    template <typename T, T...> struct integer_sequence;

    template <typename... Ts> struct list;

    /// "Evaluate" the metafunction \p T by returning the nested \c T::type
    /// alias.
    template <typename T> using eval = typename T::type;

    /// Evaluate the Metafunction Class \p F with the arguments \p Args.
    template <typename F, typename... Args>
    using apply = typename F::template apply<Args...>;

    /// A metafunction that evaluates the Metafunction Class \p F with
    /// the arguments \p Args.
    template <typename F, typename... Args> struct lazy_apply
    {
        using type = apply<F, Args...>;
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
        /// Indirection here needed to avoid Core issue 1430
        /// http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430
        template <typename... Ts> struct impl
        {
            using type = C<Ts...>;
        };

       public:
        template <typename... Ts> using apply = eval<impl<Ts...>>;
    };

    /// Turn a metafunction \p C into a Metafunction Class.
    template <template <typename...> class C> struct quote_trait
    {
        template <typename... Ts> using apply = eval<apply<quote<C>, Ts...>>;
    };

    /// Turn a class template or alias template \p F taking literals of
    /// type \p T into a Metafunction Class.
    template <typename T, template <T...> class F> struct quote_i
    {
       private:
        /// Indirection here needed to avoid Core issue 1430
        /// http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430
        template <typename... Ts> struct impl
        {
            using type = F<Ts::type::value...>;
        };

       public:
        template <typename... Ts> using apply = eval<impl<Ts...>>;
    };

    /// Turn a metafunction \p C taking literals of type \p T into a
    /// Metafunction Class.
    template <typename T, template <T...> class C> struct quote_trait_i
    {
        template <typename... Ts>
        using apply = eval<apply<quote_i<T, C>, Ts...>>;
    };

    /// Compose the Metafunction Classes in the parameter pack
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

    /// A Metafunction Class that always returns \p T.
    template <typename T> struct always
    {
        template <typename...> using apply = T;
    };

    /// A Metafunction Class partially applies the Metafunction Class \p F by
    /// binding the arguments \p Ts to the \e front of \p F.
    template <typename F, typename... Ts> struct bind_front
    {
        template <typename... Us> using apply = apply<F, Ts..., Us...>;
    };

    /// A Metafunction Class partially applies the Metafunction Class \p F by
    /// binding the arguments \p Ts to the \e back of \p F.
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
    template <typename F, typename Q = quote<list>> struct curry : compose<F, Q>
    {
    };

    /// A Metafunction Class that takes a type list \p T, unpacks the types, and
    /// then calls the Metafunction Class \p F with types.
    template <typename F> struct uncurry
    {
        template <typename T> using apply = eval<lazy_apply_list<F, T>>;
    };

    /// A Metafunction Class that reverses the order of the first two arguments.
    template <typename F> struct flip
    {
       private:
        template <typename... Ts> struct impl
        {
        };
        template <typename A, typename B, typename... Ts>
        struct impl<A, B, Ts...>
        {
            using type = apply<F, B, A, Ts...>;
        };

       public:
        template <typename... Ts> using apply = eval<impl<Ts...>>;
    };

    ////////////////////////////////////////////////////////////////////////
    /// if_
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
    }
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
    }
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
    /// parameters, with short-circuiting.
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
    /// parameters, with short-circuiting.
    template <typename... Bools> using or_ = eval<detail::_or_<Bools...>>;

    ////////////////////////////////////////////////////////////////////////
    /// list
    /// A list of types.
    template <typename... Ts> struct list
    {
        using type = list;
        /// \return `sizeof...(Ts)`
        static constexpr std::size_t size() noexcept { return sizeof...(Ts); }
    };

    ////////////////////////////////////////////////////////////////////////
    /// size
    /// An integral constant wrapper that is the size of the \c meta::list \p
    /// List.
    template <typename List> using size = meta::size_t<List::size()>;

    ////////////////////////////////////////////////////////////////////////
    /// concat
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
    }
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
    /// repeat_n
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
    }
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
    /// list_element
    /// \cond
    namespace detail
    {
        struct empty
        {
        };

        template <typename VoidPtrs> struct list_element_impl_;

        template <typename... VoidPtrs>
        struct list_element_impl_<list<VoidPtrs...>>
        {
            static empty eval(...);

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
    }
    /// \endcond

    ////////////////////////////////////////////////////////////////////////
    /// list_element
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
    /// drop
    /// \cond
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////
        /// drop_impl_
        template <typename VoidPtrs> struct drop_impl_
        {
            static empty eval(...);
        };

        template <typename... VoidPtrs> struct drop_impl_<list<VoidPtrs...>>
        {
            static empty eval(...);

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
    }
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
    /// front
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
    }
    /// \endcond

    /// Return the first element in \c meta::list \p List.
    /// \par Complexity
    /// \f$ O(1) \f$
    template <typename List> using front = eval<detail::front_<List>>;

    ////////////////////////////////////////////////////////////////////////
    /// back
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
    }
    /// \endcond

    /// Return the last element in \c meta::list \p List.
    /// \par Complexity
    /// Amortized \f$ O(1) \f$.
    template <typename List> using back = eval<detail::back_<List>>;

    ////////////////////////////////////////////////////////////////////////
    /// push_front
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
    }
    /// \endcond

    /// Return a new \c meta::list by adding the element \c T to the front of \p
    /// List.
    /// \par Complexity
    /// \f$ O(1) \f$.
    template <typename List, typename T>
    using push_front = eval<detail::push_front_<List, T>>;

    ////////////////////////////////////////////////////////////////////////
    /// pop_front
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
    }
    /// \endcond

    /// Return a new \c meta::list by removing the first element from the front
    /// of \p List.
    /// \par Complexity
    /// \f$ O(1) \f$.
    template <typename List> using pop_front = eval<detail::pop_front_<List>>;

    ////////////////////////////////////////////////////////////////////////
    /// push_back
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
    }
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
    /// empty
    /// An Boolean integral constant wrapper around \c true if \p List is an
    /// empty type list; \c false, otherwise.
    template <typename List> using empty = bool_<0 == size<List>::type::value>;

    ////////////////////////////////////////////////////////////////////////
    /// find
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
    }
    /// \endcond

    /// Return the tail of the list \p List starting at the first occurrence of
    /// \c T, if any such element exists; the empty list, otherwise.
    template <typename List, typename T>
    using find = eval<detail::find_<List, T>>;

    ////////////////////////////////////////////////////////////////////////
    /// find_if
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
    }
    /// \endcond

    /// Return the tail of the list \p List starting at the first element `A`
    /// such that `apply<Fun, A>::%value` is \c true, if any such element
    /// exists; the empty list, otherwise.
    template <typename List, typename Fun>
    using find_if = eval<detail::find_if_<List, Fun>>;

    ////////////////////////////////////////////////////////////////////////
    /// in
    /// A Boolean integral constant wrapper around \c true if there is at least
    /// one occurrence of `T` in \p List.
    template <typename List, typename T> using in = not_<empty<find<List, T>>>;

    ////////////////////////////////////////////////////////////////////////
    /// unique
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
    }
    /// \endcond

    /// Return a new \c meta::list where all duplicate elements have been
    /// removed.
    /// \par Complexity
    /// \f$ O(N^2) \f$.
    template <typename List> using unique = eval<detail::unique_<List, list<>>>;

    ////////////////////////////////////////////////////////////////////////
    /// replace
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
    }
    /// \endcond

    /// Return a new \c meta::list where all instances of type \c T have been
    /// replaced with \c U.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename T, typename U>
    using replace = eval<detail::replace_<List, T, U>>;

    ////////////////////////////////////////////////////////////////////////
    /// replace_if
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
    }
    /// \endcond

    /// Return a new \c meta::list where all elements \c A such that `apply<C,
    /// A>::%value` is \c true have been replaced with \c U.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename C, typename U>
    using replace_if = eval<detail::replace_if_<List, C, U>>;

    ////////////////////////////////////////////////////////////////////////
    /// foldl
    /// \cond
    namespace detail
    {
        template <typename List, typename State, typename Fun> struct foldl_
        {
        };

        template <typename State, typename Fun>
        struct foldl_<list<>, State, Fun>
        {
            using type = State;
        };

        template <typename Head, typename... List, typename State, typename Fun>
        struct foldl_<list<Head, List...>, State, Fun>
          : foldl_<list<List...>, apply<Fun, State, Head>, Fun>
        {
        };
    }
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
    /// foldr
    /// \cond
    namespace detail
    {
        template <typename List, typename State, typename Fun> struct foldr_
        {
        };

        template <typename State, typename Fun>
        struct foldr_<list<>, State, Fun>
        {
            using type = State;
        };

        template <typename Head, typename... List, typename State, typename Fun>
        struct foldr_<list<Head, List...>, State, Fun>
        {
            using type =
              apply<Fun, eval<foldr_<list<List...>, State, Fun>>, Head>;
        };
    }
    /// \endcond

    /// Return a new \c meta::list constructed by doing a right fold of the list
    /// \p List using binary Metafunction Class \c Fun and initial state \c
    /// State.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename State, typename Fun>
    using foldr = eval<detail::foldr_<List, State, Fun>>;

    ////////////////////////////////////////////////////////////////////////
    /// transform
    /// \cond
    namespace detail
    {
        template <typename List, typename Fun, typename = void>
        struct transform_
        {
        };

        template <typename... List, typename Fun>
        struct transform_<list<List...>, Fun, void>
        {
            using type = list<apply<Fun, List>...>;
        };

        template <typename... List0, typename... List1, typename Fun>
        struct transform_<list<List0...>, list<List1...>, Fun>
        {
            using type = list<apply<Fun, List0, List1>...>;
        };
    }
    /// \endcond

    /// Return a new \c meta::list constructed by transforming all the elements
    /// in \p List with the unary Metafuncion Class Fun. \c transform can also
    /// be called with two lists of the same length and a binary Metafunction
    /// Class, in which case it returns a new list constructed with the results
    /// of calling \c Fun with each element in the lists, pairwise.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename Fun, typename Dummy = void>
    using transform = eval<detail::transform_<List, Fun, Dummy>>;

    ////////////////////////////////////////////////////////////////////////
    /// zip_with
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
    /// zip
    /// Given a list of lists of types, construct a new list by grouping the
    /// elements from the lists pairwise into `meta::list`s.
    /// \par Complexity
    /// \f$ O(N*M) \f$, where \f$ N \f$ is the size of the outer list, and
    /// \f$ M \f$ is the size of the inner lists.
    template <typename ListOfLists>
    using zip = zip_with<quote<list>, ListOfLists>;

    ////////////////////////////////////////////////////////////////////////
    /// as_list
    /// \cond
    namespace detail
    {
        template <typename T>
        using uncvref_t = eval<std::remove_cv<eval<std::remove_reference<T>>>>;

        /// Indirection here needed to avoid Core issue 1430
        /// http://open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#1430
        template <typename Sequence> struct as_list_
        {
            using type =
              apply<uncurry<curry<quote_trait<id>>>, uncvref_t<Sequence>>;
        };
    }
    /// \endcond

    /// Turn a type into an instance of \c meta::list in a way determined by \c
    /// meta::lazy_apply_list.
    template <typename Sequence>
    using as_list = eval<detail::as_list_<Sequence>>;

    ////////////////////////////////////////////////////////////////////////
    /// reverse
    /// Return a new \c meta::list by reversing the elements in the list \p
    /// List.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List>
    using reverse = foldr<List, list<>, quote<push_back>>;

    ////////////////////////////////////////////////////////////////////////
    /// all_of
    /// A Boolean integral constant wrapper around \c true if `apply<F,
    /// A>::%value` is \c true for all elements \c A in \c meta::list \p List;
    /// \c false, otherwise.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename F>
    using all_of = empty<find_if<List, compose<quote<not_>, F>>>;

    ////////////////////////////////////////////////////////////////////////
    /// any_of
    /// A Boolean integral constant wrapper around \c true if `apply<F,
    /// A>::%value` is \c true for any element \c A in \c meta::list \p List; \c
    /// false, otherwise.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename F>
    using any_of = not_<empty<find_if<List, F>>>;

    ////////////////////////////////////////////////////////////////////////
    /// none_of
    /// A Boolean integral constant wrapper around \c true if `apply<F,
    /// A>::%value` is \c false for alls elements \c A in \c meta::list \p List;
    /// \c false, otherwise.
    /// \par Complexity
    /// \f$ O(N) \f$.
    template <typename List, typename F>
    using none_of = empty<find_if<List, F>>;

    ////////////////////////////////////////////////////////////////////////
    /// cartesian_product
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
    }
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
    /// add_const_if
    template <typename If>
    using add_const_if = if_<If, quote_trait<std::add_const>, quote_trait<id>>;

    template <bool If>
    using add_const_if_c =
      if_c<If, quote_trait<std::add_const>, quote_trait<id>>;
    /// \endcond

    ////////////////////////////////////////////////////////////////////////
    /// Math operations
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
        template <typename I1, typename I2, typename I3>
        struct integer_sequence_cat;

        template <typename T, T... N1, T... N2, T... N3>
        struct integer_sequence_cat<integer_sequence<T, N1...>,
                                    integer_sequence<T, N2...>,
                                    integer_sequence<T, N3...>>
        {
            using type =
              integer_sequence<T, N1..., (sizeof...(N1) + N2)...,
                               (sizeof...(N1) + sizeof...(N2) + N3)...>;
        };

        template <typename T, std::size_t N>
        struct make_integer_sequence_
          : integer_sequence_cat<meta::eval<make_integer_sequence_<T, N / 2>>,
                                 meta::eval<make_integer_sequence_<T, N / 2>>,
                                 meta::eval<make_integer_sequence_<T, N % 2>>>
        {
        };

        template <typename T> struct make_integer_sequence_<T, 0>
        {
            using type = integer_sequence<T>;
        };

        template <typename T> struct make_integer_sequence_<T, 1>
        {
            using type = integer_sequence<T, 0>;
        };
    }
    /// \endcond

    /// Generate \c integer_sequence containing integer constants
    /// [0,1,2,...,N-1].
    /// \par Complexity
    /// \f$ O(log(N)) \f$.
    template <typename T, T N>
    using make_integer_sequence =
      meta::eval<detail::make_integer_sequence_<T, (std::size_t)N>>;

    /// A container for a sequence of compile-time integer constants of type \c
    /// std::size_t
    template <std::size_t... Is>
    using index_sequence = integer_sequence<std::size_t, Is...>;

    /// Generate \c index_sequence containing integer constants [0,1,2,...,N-1].
    /// \par Complexity
    /// \f$ O(log(N)) \f$.
    template <std::size_t N>
    using make_index_sequence = make_integer_sequence<std::size_t, N>;

    ///@}  // group meta
} /// namespace meta

#endif

template <typename...Ts>
using Pack = meta::list<Ts...>;

template <typename Sets, typename Element>
using f = meta::concat<Sets, meta::transform<Sets, meta::bind_back<meta::quote<meta::push_front>, Element>>>;

template <typename List>
using PowerSet = meta::foldr<List, Pack<Pack<>>, meta::quote<f>>;

PowerSet<Pack<int, char, double>> foo = 42;
