void f(int) {}

int main()
{
    int const x = 5;
    auto g = [] (auto)
    {
        f(x);
    };
}