class widget
{
public:
    virtual void bar() = 0;
};

class gadget : public widget
{
public:
    void bar() override { ++counter; }
    int counter = 0;
};

int test1()
{
    gadget g;
    g.bar();
    return g.counter;
}

int test2()
{
    gadget g;
    g.bar();
    g.bar();
    return g.counter;
}

int test3()
{
    gadget g;
    g.bar();
    g.bar();
    g.bar();
    return g.counter;
}

int test4()
{
    gadget g;
    g.bar();
    g.bar();
    g.bar();
    g.bar();
    return g.counter;
}

int testloop(int n)
{
    gadget g;
    while(--n >= 0)
        g.bar();
    return g.counter;
}
