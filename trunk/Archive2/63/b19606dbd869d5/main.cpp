struct A {
    virtual ~A(){}
};

struct B {
    virtual ~B(){}
};

struct C : virtual public A, virtual public B
{
};

int main()
{
}
