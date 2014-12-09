struct A
{ 
    const A& operator=(const A&);
};

struct B : A { };

B b;

B a;

int main()
{ 
    a = b; //linker error, because of A::operator= is odr-used by implicitly-defined B::operator=
}