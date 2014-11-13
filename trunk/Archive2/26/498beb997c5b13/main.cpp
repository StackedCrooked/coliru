#include <tuple>
#include <utility>
#include <iostream>

template<class F, class...Ts, size_t...Is>
    void apply_to_each_element(F func, const std::tuple<Ts...> & tuple, std::index_sequence<Is...>){
        using expander = int[];
        (void)expander { 0, ((void)func(std::get<Is>(tuple)), 0)... };
    }
    
    template<class F, class...Ts>
    void apply_to_each_element(F func, const std::tuple<Ts...> & tuple){
        apply_to_each_element(func, tuple, std::make_index_sequence<sizeof...(Ts)>());
    }
int main() {
    auto some = std::make_tuple("I am good", 255, 2.1);
    apply_to_each_element([](const auto &x) { std::cout << x << std::endl; }, some);
}
    
    