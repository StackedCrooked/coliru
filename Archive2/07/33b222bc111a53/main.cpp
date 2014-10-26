#include <type_traits>
#include <utility>

//===============================================================================
// META-FUNCTIONS FOR EXTRACTING THE n-th TYPE OF A PARAMETER PACK

// Declare primary template
template<int I, typename... Ts>
struct nth_type_of
{
};

// Base step
template<typename T, typename... Ts>
struct nth_type_of<0, T, Ts...>
{
    using type = T;
};

// Induction step
template<int I, typename T, typename... Ts>
struct nth_type_of<I, T, Ts...>
{
    using type = typename nth_type_of<I - 1, Ts...>::type;
};

// Helper meta-function for retrieving the first type in a parameter pack
template<typename... Ts>
struct first_type_of
{
    using type = typename nth_type_of<0, Ts...>::type;
};

// Helper meta-function for retrieving the last type in a parameter pack
template<typename... Ts>
struct last_type_of
{
    using type = typename nth_type_of<sizeof...(Ts) - 1, Ts...>::type;
};

//===============================================================================
// FUNCTIONS FOR EXTRACTING THE n-th VALUE OF AN ARGUMENT PACK

// Base step
template<int I, typename T, typename... Ts>
auto nth_value_of(T&& t, Ts&&... args) ->
    typename std::enable_if<(I == 0), decltype(std::forward<T>(t))>::type
{
    return std::forward<T>(t);
}

// Induction step
template<int I, typename T, typename... Ts>
auto nth_value_of(T&& t, Ts&&... args) ->
    typename std::enable_if<(I > 0), decltype(
        std::forward<typename nth_type_of<I, T, Ts...>::type>(
            std::declval<typename nth_type_of<I, T, Ts...>::type>()
            )
        )>::type
{
    using return_type = typename nth_type_of<I, T, Ts...>::type;
    return std::forward<return_type>(nth_value_of<I - 1>((std::forward<Ts>(args))...));
}

// Helper function for retrieving the first value of an argument pack
template<typename... Ts>
auto first_value_of(Ts&&... args) ->
    decltype(
        std::forward<typename first_type_of<Ts...>::type>(
            std::declval<typename first_type_of<Ts...>::type>()
            )
        )
{
    using return_type = typename first_type_of<Ts...>::type;
    return std::forward<return_type>(nth_value_of<0>((std::forward<Ts>(args))...));
}

// Helper function for retrieving the last value of an argument pack
template<typename... Ts>
auto last_value_of(Ts&&... args) ->
    decltype(
        std::forward<typename last_type_of<Ts...>::type>(
            std::declval<typename last_type_of<Ts...>::type>()
            )
        )
{
    using return_type = typename last_type_of<Ts...>::type;
    return std::forward<return_type>(nth_value_of<sizeof...(Ts) - 1>((std::forward<Ts>(args))...));
}

//===============================================================================
// METAFUNCTION FOR COMPUTING THE UNDERLYING TYPE OF HOMOGENEOUS PARAMETER PACKS

// Used as the underlying type of non-homogeneous parameter packs
struct null_type
{
};

// Declare primary template
template<typename... Ts>
struct homogeneous_type;

// Base step
template<typename T>
struct homogeneous_type<T>
{
    using type = T;
    static const bool isHomogeneous = true;
};

// Induction step
template<typename T, typename... Ts>
struct homogeneous_type<T, Ts...>
{
    // The underlying type of the tail of the parameter pack
    using type_of_remaining_parameters = typename homogeneous_type<Ts...>::type;

    // True if each parameter in the pack has the same type
    static const bool isHomogeneous = std::is_same<T, type_of_remaining_parameters>::value;

    // If isHomogeneous is "false", the underlying type is the fictitious null_type
    using type = typename std::conditional<isHomogeneous, T, null_type>::type;
};

// Meta-function to determine if a parameter pack is homogeneous
template<typename... Ts>
struct is_homogeneous_pack
{
    static const bool value = homogeneous_type<Ts...>::isHomogeneous;
};

//===============================================================================
// META-FUNCTIONS FOR CREATING INDEX LISTS

// The structure that encapsulates index lists
template <unsigned... Is>
struct index_list
{
};

// Collects internal details for generating index ranges [MIN, MAX)
namespace detail
{
    // Declare primary template for index range builder
    template <unsigned MIN, unsigned N, unsigned... Is>
    struct range_builder;

    // Base step
    template <unsigned MIN, unsigned... Is>
    struct range_builder<MIN, MIN, Is...>
    {
        typedef index_list<Is...> type;
    };

    // Induction step
    template <unsigned MIN, unsigned N, unsigned... Is>
    struct range_builder : public range_builder<MIN, N - 1, N - 1, Is...>
    {
    };
}

// Meta-function that returns a [MIN, MAX) index range
template<unsigned MIN, unsigned MAX>
using index_range = typename detail::range_builder<MIN, MAX>::type;

//===============================================================================
// CLASSES AND FUNCTIONS FOR REALIZING LOOPS ON ARGUMENT PACKS

// Implementation inspired by @jogojapan's answer to this question:
// http://stackoverflow.com/questions/14089637/return-several-arguments-for-another-function-by-a-single-function

// Collects internal details for implementing functor invocation
namespace detail
{
    // Functor invocation is realized through variadic inheritance.
    // The constructor of each base class invokes an input functor.
    // An functor invoker for an argument pack has one base class
    // for each argument in the pack

    // Realizes the invocation of the functor for one parameter
    template<unsigned I, typename T>
    struct invoker_base
    {
        template<typename F, typename U>
        invoker_base(F&& f, U&& u) { f(u); }
    };

    // Necessary because a class cannot inherit the same class twice
    template<unsigned I, typename T>
    struct indexed_type
    {
        static const unsigned int index = I;
        using type = T;
    };

    // The functor invoker: inherits from a list of base classes.
    // The constructor of each of these classes invokes the input
    // functor with one of the arguments in the pack.
    template<typename... Ts>
    struct invoker : public invoker_base<Ts::index, typename Ts::type>...
    {
        template<typename F, typename... Us>
        invoker(F&& f, Us&&... args)
            :
            invoker_base<Ts::index, typename Ts::type>(std::forward<F>(f), std::forward<Us>(args))...
        {
        }
    };
}

// The functor provided in the first argument is invoked for each
// argument in the pack whose index is contained in the index list
// specified in the second argument
template<typename F, unsigned... Is, typename... Ts>
void for_each_in_arg_pack_subset(F&& f, index_list<Is...> const& i, Ts&&... args)
{
    // Constructors of invoker's sub-objects will invoke the functor.
    // Note that argument types must be paired with numbers because the
    // implementation is based on inheritance, and one class cannot
    // inherit the same base class twice.
    detail::invoker<detail::indexed_type<Is, typename nth_type_of<Is, Ts...>::type>...> invoker(
        f,
        (nth_value_of<Is>(std::forward<Ts>(args)...))...
        );
}

// The functor provided in the first argument is invoked for each
// argument in the pack
template<typename F, typename... Ts>
void for_each_in_arg_pack(F&& f, Ts&&... args)
{
    for_each_in_arg_pack_subset(f, index_range<0, sizeof...(Ts)>(), std::forward<Ts>(args)...);
}

// The functor provided in the first argument is given in input the
// arguments in whose index is contained in the index list specified
// as the second argument.
template<typename F, unsigned... Is, typename... Ts>
void forward_subpack(F&& f, index_list<Is...> const& i, Ts&&... args)
{
    f((nth_value_of<Is>(std::forward<Ts>(args)...))...);
}

// The functor provided in the first argument is given in input all the
// arguments in the pack.
template<typename F, typename... Ts>
void forward_pack(F&& f, Ts&&... args)
{
    f(std::forward<Ts>(args)...);
}

#include <iostream>

// Simple functor with a generic call operator that prints its input. This is used by the
// following functors and by some demonstrative test cases in the main() routine.
struct print
{
    template<typename T>
    void operator () (T&& t)
    {
        std::cout << t << std::endl;
    }
};

// This shows how a for_each_*** helper can be used inside a variadic template function
template<typename... Ts>
void print_all(Ts&&... args)
{
    for_each_in_arg_pack(print(), forward<Ts>(args)...);
}

int main()
{
    print_all(1, 2, 3, 4, 5);
}

