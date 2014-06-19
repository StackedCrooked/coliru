void f(int, int);

int main()
{
    int x = 0;
    for (int i = 0; i < 10; ++i)
    {
        if (x > 5) break;
        f(x, i*1'000'000'000);
        ++x;
    }
}