class Foo
{
public:
    Foo(int x) {};
};

void ProcessFoo(Foo& foo)
{
}

int main()
{
    ProcessFoo(Foo(42));
    return 0;
}