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

int main()
{
    gadget g;
    g.foo();    // HERE.
    return g.counter;
}
