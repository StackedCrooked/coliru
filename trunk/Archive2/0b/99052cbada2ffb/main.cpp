#include <tuple>
#include <utility>
#include <cstddef>
#include <iostream>

    template<class F, class... Ts, std::size_t... Is>
    void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func, std::index_sequence<Is...>){
        using expander = int[];
        (void)expander { 0, ((void)func(std::get<Is>(tuple)), 0)... };
    }
    
    template<class F, class...Ts>
    void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func){
        for_each_in_tuple(tuple, func, std::make_index_sequence<sizeof...(Ts)>());
    }

int main() {
    auto some = std::make_tuple("I am good", 255, 2.1);
    for_each_in_tuple(some, [](const auto &x) { std::cout << x << std::endl; });
}
    
    