
struct Foo
{
    friend auto bar(Foo)
    {
        return 0;
    }
};

int main()
{
}