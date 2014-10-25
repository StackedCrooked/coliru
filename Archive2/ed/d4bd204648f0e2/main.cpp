#include <cstddef>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

template<typename T>
struct dod;

template<typename... Ts>
struct dod<std::tuple<Ts...>> {
    std::tuple<std::vector<Ts>...> vectors;

    template<std::size_t... Is>
    void emplace_back_util(std::index_sequence<Is...>, std::tuple<Ts...> tuple) {
        ([] (auto...) { })((std::get<Is>(vectors).emplace_back(std::get<Is>(tuple)), 1)...);
    }
    
    void emplace_back(std::tuple<Ts...> tuple) {
        emplace_back_util(std::index_sequence_for<Ts...>(), std::move(tuple));
    }
};

int main() {
    dod<std::tuple<int, double, float>> xs;
    xs.emplace_back(std::make_tuple(1, 2.0, 3.0f));
    xs.emplace_back(std::make_tuple(2, 3.0, 4.0f));
    xs.emplace_back(std::make_tuple(3, 4.0, 5.0f));
    for (std::size_t i = 0; i < std::get<0>(xs.vectors).size(); ++i) {
        std::cout << "(" << std::get<0>(xs.vectors)[i] << ", " << std::get<1>(xs.vectors)[i] << ", " << std::get<2>(xs.vectors)[i] << ")\n";
    }
    return 0;
}
