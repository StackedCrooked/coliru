

struct Integer
{
    int n;
};


constexpr int foo(Integer i)
{
    return i.n < 3 ? foo(Integer{i.n+1}) : i.n;
}


int main()
{
    return foo(Integer{0});
}