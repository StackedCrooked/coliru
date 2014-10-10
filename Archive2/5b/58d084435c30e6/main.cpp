constexpr int test(int);

template<int X>
constexpr int Carlo()
{
    return test(X+3)+4;
}

constexpr int test(int x)
{
    if(x == 0)
        return Carlo<1>() + 2;
    else
        return x+5;
}

int main()
{
    constexpr auto x = test(0);
    static_assert(x == 15,"");
}
