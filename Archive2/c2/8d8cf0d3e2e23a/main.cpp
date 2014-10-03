struct A
{
    int foo();
};

int (A::* foo)() &; //works fine; was missing parenthesis.

struct B
{
    int (*bar)() &; //gcc accepts, but it is something else than you may think
};

int main()
{
    return 0;
}