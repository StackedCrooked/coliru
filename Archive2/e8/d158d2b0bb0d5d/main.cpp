#include <vector>
#include <utility>
#include <tuple>

template<int... Is>
struct seq {};

template<int N, int... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...> {};
template<int... Is>
struct gen_seq<0, Is...> : seq<Is...> {};

template<class... Ts>
struct reference_collector
{
    std::tuple<Ts...> m;
    
    reference_collector(Ts&&... pp)
    : m{std::forward<Ts>(pp)...} {}
    
    reference_collector(reference_collector const&) = delete;
    reference_collector(reference_collector&&) = delete;
    
    template<class Value_t, int... Is>
    void insert(std::vector<Value_t>& v, seq<Is...>) const
    {
        int dummy[] = {(v.emplace_back(std::get<Is>(m)), 0)...};
        (void)dummy;
    }
    
    template<class Value_t>
    operator std::vector<Value_t>() const
    {
        std::vector<Value_t> ret;
        ret.reserve(sizeof...(Ts));
        
        insert(ret, gen_seq<sizeof...(Ts)>{});
        
        return ret;
    }
};

template<class... Ts>
auto collect_references(Ts&&... pp) -> reference_collector<Ts&&...>
{
    return {std::forward<Ts>(pp)...};
}





#include <iostream>
#include <vector>
using namespace std;

struct TS{
    TS(){
        cout<<"default constructor\n";
    }

    TS(const TS &other) {
        cout<<"Copy constructor\n";
    }

    TS(TS &&other) noexcept{
        cout<<"Move constructor\n";
    }

    TS& operator=(TS const& other)
    {
        cout<<"Copy assigment\n";
        return *this;
    }

    TS& operator=(TS const&& other) noexcept
    {
        cout<<"Move assigment\n";
        return *this;
    }

    ~TS(){
        cout<<"destructor\n";
    }

};


int main()
{
    TS ts1;
    TS ts2;
    
    std::vector<TS> vec( collect_references(ts1, ts2) );
}
