struct A { void f(int); };
struct B { void f(std::string); };

struct C : A,B {};

int main()
{
    C c;
    c.f(0);
}