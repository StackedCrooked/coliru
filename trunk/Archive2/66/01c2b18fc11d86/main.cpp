namespace X
{
    class C;
    class D;
}

class X::D { };

class X::C : public X::D { };

int main()
{
}