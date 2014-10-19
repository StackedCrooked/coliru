template <class> struct type_of;

void f(int*)
{
}

int main()
{
    using T = int[];
    f(T{1, 2, 3});
}