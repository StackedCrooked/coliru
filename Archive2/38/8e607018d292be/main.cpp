void foo(int* __restrict__)
{}

int main()
{
    int x = 0;
    foo(&x);
}
