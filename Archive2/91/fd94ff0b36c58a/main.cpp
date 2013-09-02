

int foo(int n);

int test(int n)
{
    foo(n);
    return (n == 0) ? 0 : test(n - 1);
}