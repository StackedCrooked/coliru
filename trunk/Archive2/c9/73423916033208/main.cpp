#include <cstdint>
#include <type_traits>

template<std::size_t N, typename _ = void>
struct repr_for {
    using type = std::uint32_t;
};


template<std::size_t N>
struct repr_for<
    N, typename std::enable_if<(N > std::UINT32_MAX), int>::type
> {
    using type = std::uint64_t;
};

int main() {}