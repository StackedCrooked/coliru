void f() {}

int main()
{
    int (*p)() = f;
    (void)p;
}