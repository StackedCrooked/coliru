int main()
{
    int x = 42;
    auto f = []()
    {
        return [=]()
        {
            return x;
        };
    };
}