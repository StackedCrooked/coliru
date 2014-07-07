class Foo
{
public:
    Foo() = default;

    Foo(const Foo& other) : i(other.i)
    {
    }
    
private:
    int i;
};

int main()
{
    Foo a;
    Foo b(a);
    
    return 0;
}