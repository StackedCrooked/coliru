struct foo {
    const int a[1];
};

int main()
{
    const int(&ref)[1] = foo().a;
}