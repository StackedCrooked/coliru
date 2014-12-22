struct A
{
    virtual void foo();
};

struct B : A
{
    virtual void foo() const final;
};

int main() {}
