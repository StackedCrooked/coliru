#include <iostream>
#include <type_traits>

using namespace std;

struct A{
  char* ka;
};

struct B{
  char* baa;
};

template<typename T0, typename T1>
struct my_pair{
    my_pair(T0 el0, T1 el1): el0(el0), el1(el1) {}
    T0 el0;
    T1 el1; // may be next pair
};

template<typename T, int i, int current = 0>
auto constexpr get_my(const T& t, typename std::enable_if< i==current >::type* = 0) -> decltype(t.el0)
{
    return t.el0;
}

template<typename T, int i, int current = 0>
auto constexpr get_my(const T& t, typename std::enable_if< i!=current >::type* = 0) ->
    decltype( get_my<T, i, current+1>(t.el1) )
    //decltype(t.el1)
{
    return get_my<T, i, current+1>(t.el1);
}




static constexpr int make_const(const int i){
    return i;
}


int main()
{
    my_pair<int, my_pair<B,double>> p1(12.789, {B(), 3.14} );

    auto el1 = get_my<decltype(p1), 1>(p1);
    int t =1;

    //t1(3);
}
