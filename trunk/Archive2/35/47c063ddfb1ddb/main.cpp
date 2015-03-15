#include <iterator>
#include <type_traits>
#include <vector>

template<class OutputIt>
struct outit_vt
{
    struct helper : OutputIt
    {
        using typename OutputIt::container_type;
    };
    
    using value_type = typename std::remove_pointer_t<typename helper::container_type>::value_type;
};

int main()
{
    std::vector<int> v;
    auto it = std::back_inserter(v);
    static_assert(std::is_same<outit_vt<decltype(it)>::value_type, int>::value, "");
}
