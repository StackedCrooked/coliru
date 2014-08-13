#include <type_traits>
#include <tuple>

using type = typename std::result_of<decltype(std::tuple_cat<std::tuple<int>, std::tuple<short>>)>::type;

int main()
{
    type t;
}
