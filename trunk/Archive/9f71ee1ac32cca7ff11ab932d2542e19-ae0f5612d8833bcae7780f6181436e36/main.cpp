#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>

struct tie_it{
    template<class... Ts>
    std::tuple<Ts&...> operator()(Ts&... vs){
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
    bool operator()(L&& lhs, R&& rhs){
        auto access = make_access(gen_seq<sizeof...(Keys)>{});
        return access(std::forward<L>(lhs)) < access(std::forward<R>(rhs));
    }
    
    template<unsigned... Is>
    auto make_access(seq<Is...>)
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
    T&& operator()(T&& v){
        return std::forward<T>(v);
    }
};

struct user{
  int id;
  std::string name;
};

int const& get_id(user const& u){ return u.id; }
std::string const& get_name(user const& u){ return u.name; }

int main(){
    std::vector<int> v1{ 3, 5, 1, 0, 4, 8, 6, 2, 7, 9};
    std::vector<user> users{ {4, "Bjarne"}, {1, "Herb"}, {3, "Scott"}, {0, "STL"}, {2, "Andrei"} };
    
    std::sort(v1.begin(), v1.end(), compare_by(identity{}));
    for(int i : v1)
        std::cout << i << " ";
 
    std::cout << "\n";
    std::sort(users.begin(), users.end(), compare_by(get_id));
    for(auto& u : users)
        std::cout << "(" << u.id << ", " << u.name << ") ";
        
    std::cout << "\n";
    std::sort(users.begin(), users.end(), compare_by(get_name));
    for(auto& u : users)
        std::cout << "(" << u.id << ", " << u.name << ") ";
}