

struct A
{
    virtual void foo() {}
};

struct B
{
    virtual void foo() {}
};


struct AB : A, B
{
};


int main()
{
    AB ab;
    ab.foo();
}