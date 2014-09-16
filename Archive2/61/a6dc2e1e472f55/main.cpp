
template <typename...>
struct _ {};

struct A
{
    template <class T1, class T2, class T3>
    A(_<T1, T2, T3>) {}
};

int main()
{
    A a{_<int, double, char>{}};
}
