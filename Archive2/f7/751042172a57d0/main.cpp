#include <map>

template <template <typename...> class Container>
struct make_container
{
    template <typename... Args>
    using type = Container<Args...>;
};

int main()
{
    make_container<std::map>::type<int, int> m;
}

