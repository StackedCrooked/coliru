enum { a };

template <class T>
struct foo
{
    static constexpr auto value = a;
};

int main()
{
    static constexpr auto r = foo<int>::value;
}
