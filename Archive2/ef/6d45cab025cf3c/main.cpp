#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>

template<size_t... Args>
struct index_seq {};

template<size_t CurInd, size_t... Indexes>
struct make_index_seq_helper
{
    typedef typename make_index_seq_helper<CurInd-1, CurInd-1, Indexes...>::type type;
};

template<size_t... Indexes>
struct make_index_seq_helper<0, Indexes...>
{
    typedef index_seq<Indexes...> type;
};

template<size_t Size>
using make_index_seq = typename make_index_seq_helper<Size>::type;

template<typename F, typename Tuple, size_t... Seq>
auto call_impl(F f, Tuple t, index_seq<Seq...>)
{
    return f(std::get<Seq>(t)...);
}

template<typename F, typename... Args>
auto call(F f, std::tuple<Args...> t)
{
    return call_impl(f, t, make_index_seq<sizeof...(Args)>{});
}

void foo(int i, double j)
{
    std::cout << i << " " << j;
}

template<typename... Args>
class stream_reader
{
    public:
    stream_reader(Args&... args) 
        : t_(args...)
    {}
    void extract(std::istream& is)
    {
        extract_impl(is, make_index_seq<sizeof...(Args)>{});
    }
    private:
    template<size_t... Seq>
    void extract_impl(std::istream& is, index_seq<Seq...>)
    {
        do_extract(is, std::get<Seq>(t_)...);
    }    
    
    template<typename First, typename... As>
    void do_extract(std::istream& is, First& f, As&... tail)
    {
        is >> f;
        do_extract(is, tail...);
    }
    
    void do_extract(std::istream& is)
    {
    }
    
    private:
    std::tuple<Args&...> t_;
};

int main()
{
    //auto t = std::make_tuple(1, 2.0);
    //call(foo, t);
    
    int i;
    double j;
    
    stream_reader<int, double> sr(i, j);
    
    std::stringstream ss("2 34.87");
    sr.extract(ss);
    
    std::cout << i << " " << j << std::endl;
}
