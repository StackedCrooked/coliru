#include <array>

template <int... Values>
struct pack {};

template <int... Values>
std::array<int, sizeof...(Values)> const& get_values(pack<Values...>) {
    static constexpr std::array<int, sizeof...(Values)> array = {{
        Values...
    }};
    return array;
}

int main() {
    get_values(pack<0,1,2,3>{});
}