struct B
{
    B(){ }
    B(const B&){}
};

struct A : B
{
    A(){ };
};

const A a;

A t = a;

int main(){ }

