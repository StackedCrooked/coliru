
#include <tuple>
#include <sstream>
#include <iostream>

//indecies trick
template <std::size_t... Is>
struct indices {};

template <std::size_t N, std::size_t... Is>
struct build_indices
  : build_indices<N-1, N-1, Is...> {};

template <std::size_t... Is>
struct build_indices<0, Is...> : indices<Is...> {};
//end indecies trick



template<class... Ts, std::size_t... Is>
std::istream& read(std::istream& in, std::tuple<Ts...>& t, indices<Is...>) 
{
    using for_each_variadic=int[];
    for_each_variadic{(   in>>std::get<Is>(t)   ,0)...,0}; 
    return in;
}

template<class... Ts>
std::istream& read(std::istream& in, std::tuple<Ts...>& t) 
{return read(in,t,build_indices<sizeof...(Ts)>());}



int main (int, char *[])
{
    std::istringstream istr("1 2");
    std::tuple<int, double> t;
    read(istr, t);
    std::cout << std::get<1>(t);
}