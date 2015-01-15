class Foo
{
public:
    Foo(const Foo&) = delete;
    Foo& operator=(const Foo&) = delete;
};


int main()
{
    Foo foo;
}
