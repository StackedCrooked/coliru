#include <tuple>
#include <iostream>

template<typename H, typename T>
struct typelist
{
    typedef H Head;
    typedef T Tail;
};

struct null_typelist {};


template<int... Indices>
struct indices {
    using next = indices<Indices..., sizeof...(Indices)>;
};

template<int Size>
struct build_indices {
    using type = typename build_indices<Size - 1>::type::next;
};

template<>
struct build_indices<0> {
    using type = indices<>;
};

template<typename T>
using Bare = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template<typename Tuple>
constexpr
typename build_indices<std::tuple_size<Bare<Tuple>>::value>::type
make_indices()
{ return {}; }

template<typename T, typename... Args>
struct tuple_push;

template<typename T, typename... Args>
struct tuple_push<T, std::tuple<Args...>>
{
    typedef std::tuple<Args..., T> type;
};

template<typename TL>
struct typelist_to_tuple;

template<typename H, typename T>
struct typelist_to_tuple<typelist<H, T>>
{
    typedef typename tuple_push<H, typename typelist_to_tuple<T>::type>::type type;
};

template<typename H>
struct typelist_to_tuple<typelist<H, null_typelist>>
{
    typedef std::tuple<H> type;
};

struct Float {
  float get() const { return 7.5; }
};
struct Int {
  int get() const { return 7; }
};

template<typename... Args>
void foo(const Args&... args)
{
}

template<typename T, typename... Args>
void foo(const T& current, const Args&... args)
{
    std::cout << current << std::endl;
    foo(args...);
}

template<typename T>
auto apply_impl(const T& value) -> decltype(value.get())
{
    return value.get();
}

template<typename T>
auto apply_impl(const T& value) -> decltype(std::cout << value, value)
{
    return value;
}

template<typename Tuple, int... Indices>
void apply(const Tuple& tuple, indices<Indices...>)
{
   foo(apply_impl(std::get<Indices>(tuple))...);
}

template<typename Tuple>
void apply(const Tuple& tuple)
{
    apply(tuple, make_indices<Tuple>());
}

int main()
{
    typedef typelist<Int, typelist<Float, typelist<Int, null_typelist>>> list;
    typedef typelist_to_tuple<list>::type tuple1;
    typedef tuple_push<int, tuple1>::type tuple;
    tuple t = std::make_tuple(Int(), Float(), Int(), 10);
    apply(t);
}