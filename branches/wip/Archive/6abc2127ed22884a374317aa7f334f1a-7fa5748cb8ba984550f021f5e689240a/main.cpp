int x = 42;

void f()
{
        int y = 43;

        static_assert(&x != &y, "foo");
}

int main()
{
        f();
}