#include <iterator>
#include <type_traits>
#include <vector>

template<typename T>
struct outit_v {
    using container_type = typename T::container_type;
    using value_type = typename container_type::value_type;
};

int main()
{
    std::vector<int> v;
    auto it = std::back_inserter(v);
    static_assert(std::is_same<outit_v<decltype(it)>::value_type, int>::value, "");
}