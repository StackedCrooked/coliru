class A { void foo(); };

class B : private A { ::A A; public: using A::foo; };

int main()
{
    B b;
    b.foo();
}