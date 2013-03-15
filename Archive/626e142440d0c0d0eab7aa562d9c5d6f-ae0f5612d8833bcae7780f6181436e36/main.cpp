#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>

struct tie_it{
    template<class... Ts>
    std::tuple<Ts&...> operator()(Ts&... vs) const{
        return std::tie(vs...);
    }
};

template<unsigned...> struct seq{};

template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<class... Keys>
struct compare_by_{
    std::tuple<Keys...> keys;
    
    template<class L, class R>
    bool operator()(L&& lhs, R&& rhs) const{
        auto access = make_comp(gen_seq<sizeof...(Keys)>{});
        return access(std::forward<L>(lhs)) < access(std::forward<R>(rhs));
    }
    
    template<unsigned... Is>
    auto make_comp(seq<Is...>) const
      -> decltype(std::bind(tie_it{}, std::bind(std::get<Is>(keys), std::placeholders::_1)...))
    {
        return std::bind(tie_it{}, std::bind(std::get<Is>(keys), std::placeholders::_1)...);
    }
};

template<class... Keys>
compare_by_<Keys...> compare_by(Keys... ks){ return {std::tuple<Keys...>{ks...}}; }

#include <vector>
#include <iostream>
#include <algorithm>

struct identity{
    template<class T>
    T&& operator()(T&& v) const{
        return std::forward<T>(v);
    }
};

enum status_t { online, away, offline };

struct user {
    user(const std::string & n, status_t st) : name_(n), status_(st) {}
    const std::string & name() const { return name_; }
    status_t status() const { return status_; }    
    std::string name_;
    status_t status_;
};

int main(){
    std::vector<int> v1{ 3, 5, 1, 0, 4, 8, 6, 2, 7, 9};
    
    using namespace std::placeholders;
    
    std::sort(v1.begin(), v1.end(), compare_by{bind(&user::status, _1), bind(&user::name, _2)});
    for(int i : v1)
        std::cout << i << " ";
}