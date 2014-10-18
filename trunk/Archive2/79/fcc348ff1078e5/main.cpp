void f(int (&&)[3])
{
}

int main()
{
    using T = int[];
    f(T{1, 2, 3});
}