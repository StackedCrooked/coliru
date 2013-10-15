struct S
{
protected:
    int x;

public:
    void foo(S& p)
    {
        p.x = 42;
    }
};

int main()
{
    S s1;
    S s2;
    s1.foo(s2);
}
