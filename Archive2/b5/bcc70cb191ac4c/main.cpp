constexpr unsigned f(unsigned x)
{
    while (x & 1) x *= 3;
    return x;
}

int main()
{
    char a[f(2)];
    char b[f(1)];
}
