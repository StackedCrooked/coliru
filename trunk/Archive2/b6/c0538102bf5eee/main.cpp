#include <memory>
#include <tuple>

template<class...ts>
auto get_last3(ts&... vs) 
-> decltype(std::get<sizeof...(vs)-1>(std::tie(vs...)))
{return std::get<sizeof...(vs)-1>(std::tie(vs...));}




int main() {
    //int t = get_last(3, 4, 5);
    //int u = get_last2(3, 4, 5);
    int a=3,b=4,c=5;
    int v = get_last3(a, b, c);
}