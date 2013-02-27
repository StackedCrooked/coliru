#include <array>

template <int... Values>
struct pack {};

template <int... Values>
constexpr std::array<int, sizeof...(Values)> get_values(pack<Values...>) {
    return {{ Values... }};
}

static constexpr auto data = get_values(pack<0,1,2,3>{});

int main() {
}