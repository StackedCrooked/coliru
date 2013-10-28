template <typename>
struct Foo
{
    Foo()
    {
        int t(int()); // OK
    }
};

int main()
{
    int t(int()); // OK
    Foo<int> a; // OK
}