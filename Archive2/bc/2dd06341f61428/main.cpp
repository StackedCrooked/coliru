
template<typename, template<typename...> class, typename...>
struct Test
{
};
template<typename, typename...>
struct Test
{
};

template<typename...>
struct SomeTemplate
{
};

int main()
{
    Test<int, short, long, float> t1;
    Test<int, SomeTemplate, double, bool> t2;
}
