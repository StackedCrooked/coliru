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
inline void foreach_cross(F f, std::pair<I, I> h,
                               std::pair<Is, Is>... t) {
    while(h.first != h.second) {
        foreach_cross([&](Is... ts){
                          f(h.first, ts...);
                      }, t...);
        h.first++;
    }
}

template<typename O, typename... Is>
void cross(O& out, std::pair<Is, Is>... in) {
    foreach_cross([&](Is... ts){
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
    cross(back_ins, std::make_pair(is.begin(), is.end()),
                    std::make_pair(cps.begin(), cps.end()),
                    std::make_pair(ds.begin(), ds.end()));
    for(auto& a: res) {
        std::cout << '{' << std::get<0>(a) << ',' <<
                            std::get<1>(a) << ',' <<
                            std::get<2>(a) << "}\n";
    }
}