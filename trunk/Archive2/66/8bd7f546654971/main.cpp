#include <array>
#include <cstdio>

template <size_t N>
struct bar {
        template <typename T, typename ...Tn>
        static constexpr auto apply(T v, Tn ...vs)
            -> decltype(bar<N - 1>::apply(v, v, vs...))
        {
                return bar<N - 1>::apply(v, v, vs...);
        }
};

template <>
struct bar<1> {
        template <typename T, typename ...Tn>
        static constexpr auto apply(T v, Tn ...vs)
            -> std::array<T, sizeof...(vs) + 1>
        {
                return std::array<T, sizeof...(vs) + 1>{v, vs...};
        }

};

template <typename T, size_t N>
struct foo {
        std::array<T, N> data;

        constexpr foo(T val)
        : data(bar<N>::apply(val))
        {}
};

int main(int argc, char **argv)
{

        constexpr foo<int, 10> f(5);
        for (auto d: f.data)
                printf("%d", f.data[d]);

    	printf("\n");
        return 0;
}
