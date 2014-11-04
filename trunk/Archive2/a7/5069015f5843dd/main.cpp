struct A
{
    A(){ };
    A(A&){ };
};

const A a;

A t = a;

int main(){ }

