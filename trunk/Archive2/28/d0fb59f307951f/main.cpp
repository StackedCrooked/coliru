class a
{
public:
    int foo();
};

auto a::foo()
{
    return 1;
}

int main()
{
    return a{}.foo();
}
