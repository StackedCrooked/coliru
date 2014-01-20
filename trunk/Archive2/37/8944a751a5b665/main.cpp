void foo(char[20][20]) {}

int main()
{
    char a[42][20];
    char(*p)[20] = a;
    foo(a);
    foo(p);
}