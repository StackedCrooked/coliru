struct A { static void f(); };

int main()
{
    auto f = &A::f;
}