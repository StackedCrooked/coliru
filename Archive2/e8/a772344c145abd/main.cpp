#include <cstddef>
#include <iostream>
#include <tuple>

struct A
{
    std::size_t size()
    {
        return 3;
    }
};

struct B
{
    std::size_t size()
    {
        return 2;
    }
};

struct C
{
    std::size_t size()
    {
        return 4;
    }
};

template <typename Tuple>
struct Foo
{
    const Tuple& tuple_;
    std::array<int, std::tuple_size<Tuple>::value> array_;

    Foo(const Tuple& tuple) : tuple_(tuple)
    {
        std::cout << init() << '\n';
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <std::size_t INDEX = 0>
    typename std::enable_if<std::tuple_size<Tuple>::value == INDEX, std::size_t>::type
    init()
    {
        return 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <std::size_t INDEX = 0>
    typename std::enable_if<std::tuple_size<Tuple>::value != INDEX, std::size_t>::type
    init()
    {
        auto offset = init<INDEX + 1>();

        std::cout << "index: "<< INDEX << "; offset: " << offset << '\n';

        array_[INDEX] = offset;

        return offset + std::get<INDEX>(tuple_).size();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <std::size_t INDEX = 0, typename T>
    typename std::enable_if<std::tuple_size<Tuple>::value == INDEX, std::size_t>::type
    offset(const T&)
    {
        return 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <std::size_t INDEX = 0, typename T>
    typename std::enable_if<(std::tuple_size<Tuple>::value != INDEX) && !std::is_same<typename std::decay<typename std::tuple_element<INDEX, Tuple>::type>::type, T>::value, std::size_t>::type
    offset(const T& t)
    {
        return offset<INDEX + 1>(t);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <std::size_t INDEX = 0, typename T>
    typename std::enable_if<(std::tuple_size<Tuple>::value != INDEX) && std::is_same<typename std::decay<typename std::tuple_element<INDEX, Tuple>::type>::type, T>::value, std::size_t>::type
    offset(const T&)
    {
        return array_[INDEX];
    }    
};

int main()
{
    A a;
    B b;
    C c;
    auto t = std::tie(a, b, c);
    using T = decltype(t);
    Foo<T> foo(t);

    std::cout << foo.offset(a) << '\n';
    std::cout << foo.offset(b) << '\n';
    std::cout << foo.offset(c) << '\n';
}
