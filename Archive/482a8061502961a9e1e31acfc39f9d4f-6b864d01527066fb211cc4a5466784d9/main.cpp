void f()
{
        int y[2] = { 42, 43 };

        static_assert(&y[0] < &y[1], "foo");
}

int main()
{
        f();
}