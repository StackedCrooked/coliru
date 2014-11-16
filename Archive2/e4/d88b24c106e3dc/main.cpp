struct foo
{
    int a[0];
    foo() : a() {}
};

int main()
{
    foo f;
}