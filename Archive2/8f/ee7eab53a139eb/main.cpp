#include<tuple>
#include<vector>

// foreach_cross(f, vs...) means
// "do `f` for each element of Cartesian product of vs..."
// given as iterators

template<typename F>
inline void foreach_cross(F f) {
    f();
}
template<typename F, typename I, typename... Is>
inline void foreach_cross(F f, I hbegin, I hend,
                               Is... t) {
    while(hbegin != hend) {
        foreach_cross([=](auto... ts){
                          f(hbegin, ts...);
                      }, t...);
        hbegin++;
    }
}

template<typename O, typename... Is>
void cross(O& out, Is... in) {
    foreach_cross([&](auto... ts){
                      *out++ = std::make_tuple(*ts...);
                  }, in...);
}

#include<iostream>
#include<set>
#include<list>

int main() {
    std::vector<int> is = {2,5,9};
    std::list<char const*> cps = {"foo","bar"};
    const std::set<double> ds = {1.5, 3.14, 2.71};
    std::vector<std::tuple<int, char const*, double>> res;
    auto back_ins = std::back_inserter(res);
    cross(back_ins, is.begin(), is.end(),
                    cps.begin(), cps.end(),
                    ds.begin(), ds.end());
    for(auto& a: res) {
        std::cout << '{' << std::get<0>(a) << ',' <<
                            std::get<1>(a) << ',' <<
                            std::get<2>(a) << "}\n";
    }
}