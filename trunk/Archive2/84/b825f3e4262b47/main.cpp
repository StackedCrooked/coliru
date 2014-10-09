template<typename T>
struct bar
{
};

template<>
struct bar<int>
{
    struct X { using type = int; };
    using type = X;
};

template<typename T>
struct foo : bar<T>::type {};

template<typename T>
typename foo<T>::type test(int) { return {}; }

template<typename T>
void test(...);

int main()
{
    test<int>(0);
    test<double>(0);
}