struct A
{
    virtual void foo();
};

struct B : A
{
    virtual void foo() const override final;
};

int main() {}
