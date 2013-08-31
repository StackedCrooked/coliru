class widget
{
public:
    void foo() { bar(); }

private:
    virtual void bar() = 0;
};

class gadget final : public widget
{
    void bar() override final { ++counter; }
public:
    int counter = 0;
};

int test1()
{
    gadget g;
    g.foo();
    return g.counter;
}

int test2()
{
    gadget g;
    g.foo();
    g.foo();
    return g.counter;
}

int test3()
{
    gadget g;
    g.foo();
    g.foo();
    g.foo();
    return g.counter;
}

int test4()
{
    gadget g;
    g.foo();
    g.foo();
    g.foo();
    g.foo();
    return g.counter;
}

int testloop(int n)
{
    gadget g;
    while(--n >= 0)
        g.foo();
    return g.counter;
}
