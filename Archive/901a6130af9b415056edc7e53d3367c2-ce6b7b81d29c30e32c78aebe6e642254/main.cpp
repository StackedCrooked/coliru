template<typename... T>
struct caller
{
    template<T... F>
    static void f()
    {
    }
};

int main()
{
    caller<int>::f<1>();
    caller<int, char, int>::f<1, 'a', 1>();
}