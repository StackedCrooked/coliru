template<typename... T>
struct foo {
    static constexpr auto N = sizeof...(T);

    struct bar {
        static_assert( N == 3, "" );
        static_assert( (-1) % 3 == -1, "" );
        static_assert( (-1) % N != -1, "" );
    };
};

int main()
{
    foo<int, int, int>::bar();
}