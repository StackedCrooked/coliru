template<typename T>
struct foo {};

template<typename T>
void bar(foo<T>, foo<T>) {}

template<typename T>
struct convertible {
    operator foo<T>() { return {}; }
};

int main()
{
    bar(foo<int> {}, (foo<int>)convertible<int> {});
}