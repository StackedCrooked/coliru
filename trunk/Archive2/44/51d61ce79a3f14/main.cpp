#include <utility>
#include <string>
#include <unordered_map>
#include <functional>
#include <boost/variant.hpp>

template<class V>
struct construct{
    template<class T>
    V operator()(T&& v) const{
        return {std::forward<T>(v)};
    }
};

template<class L, class R>
struct composed{
    L l; R r;
    
    template<class... Args>
    auto operator()(Args&&... args) const{
        return r(l(std::forward<Args>(args)...));
    }
};

template<class L, class R>
composed<L, R> chain(L l, R r){ return {l, r}; }

template<class V, class... Args>
using factory_dict = std::unordered_map<std::string, std::function<V(Args...)>>;

template<class V, class... Args, class F>
void add(factory_dict<V, Args...>& map, std::string id, F f){
    map.emplace(std::move(id), chain(std::move(f), construct<V>{}));
}

struct A{ int i = 1; };
struct B{ int i = 2; };

template<class T, class... Args>
T factory(Args&&... args){
    return T(std::forward<Args>(args)...);
}

using var_types = boost::variant<A, B>;

#include <iostream>

int main(){
    factory_dict<var_types> factories;
    add(factories, "A", factory<A>);
    add(factories, "B", factory<B>);
    auto v = factories["A"]();
    std::cout << v.which() << "\n";
    v = factories["B"]();
    std::cout << v.which() << "\n";
}