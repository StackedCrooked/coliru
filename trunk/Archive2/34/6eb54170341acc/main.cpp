#include <iterator>
#include <type_traits>
#include <vector>

template<class OutputIt>
struct outit_vt
:
    OutputIt
{
    using self_type = outit_vt<OutputIt>;
    using value_type = typename std::remove_pointer_t<decltype(std::declval<self_type>().container)>::value_type;
};

int main()
{
    std::vector<int> v;
    auto it = std::back_inserter(v);
    static_assert(std::is_same<outit_vt<decltype(it)>::value_type, int>::value, "");
}
