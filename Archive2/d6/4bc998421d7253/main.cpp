void f(int*)
{
}

int main()
{
    using T = int[];
    f(int[]{1, 2, 3});
}