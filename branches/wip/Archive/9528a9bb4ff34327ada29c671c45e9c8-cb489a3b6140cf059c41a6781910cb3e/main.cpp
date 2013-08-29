#include <tuple>
#include <tuple>
#include <type_traits>
#include <vector>

template <template<class...> class, class>
struct update_tuple;

template <template <class...> class T, class... Args>
struct update_tuple<T, std::tuple<Args...>>
{
    using type = std::tuple<T<Args>...>;
};

int main()
{
    static_assert
    (
        std::is_same
        <
            std::tuple<std::vector<int>, std::vector<double>>,
            update_tuple<std::vector, std::tuple<int, double>>::type
        >::value,
        "They are not same"
    );
    return 0;
}
