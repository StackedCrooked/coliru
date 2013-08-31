#define BOOST_RESULT_OF_USE_DECLTYPE
#include <algorithm>
#include <boost/iterator/function_input_iterator.hpp>
#include <boost/range/algorithm.hpp>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <random>
#include <vector>
#include <limits>
#include <boost/phoenix.hpp>

using namespace std;
using namespace boost::phoenix::arg_names;

namespace {

    static constexpr auto NUM_SAMPLES = 1ul << 4;

    ////////////////////////////////////////////////////////
    // generating random sample data
    static mt19937 rand_engine;

    template<template<typename...> class Container, typename T>
        Container<T> generate(typename std::enable_if<std::numeric_limits<T>::is_integer>::type* = nullptr)
    {
        static auto f = bind(uniform_int_distribution<T>(numeric_limits<T>::lowest()), rand_engine);
        return { 
            boost::make_function_input_iterator(f, 0ul),
            boost::make_function_input_iterator(f, NUM_SAMPLES) 
        };
    }

    template<template<typename...> class Container, typename T>
        Container<T> generate(typename std::enable_if<!std::numeric_limits<T>::is_integer>::type* = nullptr)
    {
        static auto f = bind(uniform_real_distribution<T>(-5, +5), rand_engine);
        return {
            boost::make_function_input_iterator(f, 0ul),
            boost::make_function_input_iterator(f, NUM_SAMPLES) 
        };
    }
}

template<template<typename...> class Container>
struct ContainerTests
{
    template<typename T, typename U, typename... Ts> 
        static void run()
    {
        run<T>();
        run<U, Ts...>();
    }

    template<typename T> 
        static void run()
    {
        auto data = generate<Container, T>();
        std::cout << "\n=========== " << typeid(data).name() << "\n";
        for (auto i : data)
            std::cout << i << " ";
    }
};

template <typename... T>
struct TestRunner
{
    template<template<typename...> class C1, template<typename...> class C2, template<typename...> class... Cs>
        static void dispatch()
    {
        ContainerTests<C1>::template run<T...>();
        dispatch<C2, Cs...>();
    }

    template<template<typename...> class C>
        static void dispatch()
    {
        ContainerTests<C>::template run<T...>();
    }
};

int main()
{
    TestRunner<signed, unsigned, double>::dispatch<std::vector, std::list, std::deque>();
}
