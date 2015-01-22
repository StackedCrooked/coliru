void foo(long * a)
{
    *a = 50;
}

int main()
{
    const long a = 7; 
    const long * b = &a;

    foo(b);
}