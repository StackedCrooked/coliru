template <class T>
void f(T) {}

struct A { void f(); };

int main()
{
    f(&A::f);
}