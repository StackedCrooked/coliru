#include <iostream>
#include <tuple>

typedef std::tuple<const char*>            case_0;
typedef std::tuple<const char*,int>        case_1i;
typedef std::tuple<const char*,double>     case_1d;
typedef std::tuple<const char*,int,int>    case_2ii;
typedef std::tuple<const char*,int,double> case_2id;

template<typename...Args>
auto foo(std::tuple<Args...> & tpl) -> decltype(std::get<0>(tpl))&
{
     return std::get<0>(tpl);
}

template<typename...Args>
auto v0(std::tuple<Args...> & tpl) -> decltype(std::get<1>(tpl))&
{
     return std::get<1>(tpl);
}

template<typename...Args>
auto v1(std::tuple<Args...> & tpl) -> decltype(std::get<2>(tpl))&
{
     return std::get<2>(tpl);
}

//////////////////////////////////
template<size_t...>
struct seq {};

template<size_t M, size_t ...N>
struct genseq  : genseq<M-1,M-1, N...> {};

template<size_t ...N>
struct genseq<0,N...>
{
    typedef seq<N...> type;
};

/////////////////////////////////////
struct sink
{
    template<typename ...Args>
    sink(Args const & ...) {}
};
template<typename ...Args, size_t ...N>
void do_print(std::ostream& out, std::tuple<Args...> const & tpl, seq<N...>)
{
    sink s { (out << std::get<N>(tpl) << "\n" )... };
}

template<typename ...Args>
std::ostream& operator << (std::ostream& out, std::tuple<Args...> const & tpl)
{
    const size_t N = sizeof...(Args);
    do_print(out, tpl, typename genseq<N>::type());
    return out;
}

int main()
{
    case_2id a;
    foo(a) = "hello";
    v0(a) = 1202;
    v1(a) = 10.2;
    std::cout << a << std::endl; //print all values!
}