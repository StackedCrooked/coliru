void f(int);

int main()
{
    for (int i = 0; i < 10; ++i)
    {
        f(i*1'000'000'000);
    }
}