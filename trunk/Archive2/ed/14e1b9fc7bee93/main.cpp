struct A{ };

struct B
{
    B(){ };
    operator A(){ return A(); }
};

const B b;

void foo(A){ };

int main(){ foo(b); }