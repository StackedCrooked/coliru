#include <tuple>
#include <iostream>

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_LIST_SIZE 30
#define BOOST_MPL_LIMIT_VECTOR_SIZE 30

#include <boost/variant.hpp>

template<typename... Ts>
using algebraic_datatype  = boost::variant<Ts...>;

template<typename T>
using algebraic_recursive = boost::recursive_wrapper<T>;

template<int...>
struct seq { };

template<int N, int... S>
struct gens : gens<N-1, N-1, S...> { };

template<int... S>
struct gens<1, S...> {
  typedef seq<S...> type;
};

template<typename T>
struct Match
{
    void print(T const& t) const
    {
        std::cout << t;
    }
};

template<typename T>
struct Match<std::tuple<T>>
{
    void print(std::tuple<T> const& t) const
    {
        Match<T>().print(std::get<0>(t));
    }
};

template<typename... Ts>
struct Match<algebraic_datatype<Ts...>> : boost::static_visitor<>
{
    template<typename T>
    void operator()(T const& t) const
    {
        Match<T>().print(t);
    }
    
    void print(algebraic_datatype<Ts...> const& ad) const
    {
        std::cout << R"(")";
        boost::apply_visitor(Match<algebraic_datatype<Ts...>>(), ad);
        std::cout << R"(")";
    }
};

template<typename T>
struct Match<std::vector<T>>
{
    void print(std::vector<T> const& vec) const
    {
        std::cout << "[";
        std::string delimiter = "";
        for(T t : vec)
        {
            std::cout << delimiter;
            Match<T>().print(t);
            delimiter = ", ";
        }
        std::cout << "]";
    }
};

template<typename T, typename... Ts>
struct Match<std::tuple<T, Ts...>>
{
    void print(std::tuple<T, Ts...> const& args) const
    {
        std::cout << "(";
        Match<T>().print(std::get<0>(args));
        std::cout << ", ";
        call_recursive(args, typename gens<sizeof...(Ts) + 1>::type());
        std::cout << ")";
    }

    template<int... S>
    void call_recursive(std::tuple<T, Ts...> const& args, seq<S...>) const
    {
         Match<std::tuple<Ts...>>().print(std::make_tuple(std::get<S>(args)...));
    }
};

// Unpack any tuple, and sub-tuples, and pass all leaf members to cout.
// We can extend this, to algebraic datatypes easily.

// For hooking in a semantic leaf action, do;
/*
template<>
struct Match<double>
{
    void print(double d)
    {
        std::cout << "double";
    }
};
*/
// The above will make all double leaves print 'double', rather than the double value.
// In a similar way, we can do this, for composite nodes;
/*
template<>
struct Match<std::vector<int>>
{
    void print(std::vector<int> const& vec) const
    {
        std::cout << "INTEGER VECTOR";
    }
};
*/
// The above will make all std::vecto<int> leaves print 'INTEGER VECTOR', rather than the unpacked values.

/*
using binop_expression = std::tuple<exp, binop, exp>;
template<typename exp1, typename exp2>
struct Match<binop_expression<exp1, Binop::Lazy_or, exp2>>
{
};
*/

using strings = std::vector<std::string>;
using ints = std::vector<int>;
using strings_or_ints = algebraic_datatype<strings, ints>;
using magic = std::tuple<char, strings_or_ints, double>;

int main()
{
    /*
    auto m1 = Match<int>();
    m1.print(2);
    auto m2 = Match<std::tuple<int, double, int>>();
    m2.print(std::make_tuple(3, 4.5, 6));
    */
    auto m3 = Match<magic>();
    
    //strings_or_ints s_or_i = strings_or_ints(strings{"R2D2", "C-PO"});
    strings_or_ints s_or_i = strings_or_ints(ints{1,2,3});
    magic m = std::make_tuple('c', s_or_i, 1.5);
    
    m3.print(m);
}