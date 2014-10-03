struct A
{
    int foo();
};

int (A::* foo)() &; //works fine; was missing parenthesis.

struct B
{
    int (*bar)() &; //gcc accepts though I believe it _should_ be ill-formed.
};

int main()
{
    return 0;
}