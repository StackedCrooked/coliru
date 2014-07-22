#include <string>
#include <iostream> 

template <template <class...> class TT, class T, class... Rest>
struct Tail
{
    using type = TT<Rest...>;
};

template <class... Ts>
struct Bar
{
    static constexpr uint size = sizeof...(Ts);
};

template <class... Ts>
struct Foo
{
    static constexpr uint size = sizeof...(Ts);

    using TailBar = typename Tail<Bar, Ts...>::type;
    static constexpr uint bar_size = TailBar::size;
};

int main(int argc, char *argv[])
{
    using ZZZ = Foo<int, int, int>;
    std::cout << "Size:" << ZZZ::size << " Bar size:" << ZZZ::bar_size << std::endl;
}