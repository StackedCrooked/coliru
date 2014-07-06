int foo()
{
    static int block_scope;
    return block_scope;
}

struct S
{
    int m;
    S() : m(foo()) {}
};

int main()
{
    S s;
}