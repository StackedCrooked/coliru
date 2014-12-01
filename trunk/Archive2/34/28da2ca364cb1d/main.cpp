struct A;

struct B
{
    operator A();
};

struct A
{
    A(A const&){}
};

A a{B()};
