#include <tuple>
#include <vector>

template<typename T>
struct dod;

template<typename... Ts>
struct dod<std::tuple<Ts...>> {
    std::tuple<std::vector<Ts>...> vectors;
};

int main() {
    dod<std::tuple<int, double, float>> xs;
}
