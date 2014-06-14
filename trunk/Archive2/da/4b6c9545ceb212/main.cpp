namespace
    long_and_ugly
{
    enum class
        colour
    {
        red,
        green,
        blue
    };
}

int main()
{
    using long_and_ugly::colour;
    auto x = red;
}