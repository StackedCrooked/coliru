constexpr int Buratino(int);

template<int X>
constexpr int Carlo()
{
    return Buratino(X+3)+4;
}

constexpr int Buratino(int x)
{
    if(x <= 0)
        return Carlo<1>() + 2;
    else
        return x+5;
}

int main()
{
    static_assert(Buratino(0) == 15, "");
}
