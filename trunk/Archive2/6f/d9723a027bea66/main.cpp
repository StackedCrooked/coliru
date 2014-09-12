template <typename T>
struct A
{
    template <typename U>
    struct AA
    {
    };
};

template <typename V, template <typename> class W = A<V>::template AA>
struct B
{
};

int main()
{
    B<int> b;
    (void)b;
}
