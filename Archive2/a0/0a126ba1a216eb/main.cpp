struct Point
{
    int x = 5;
    constexpr int size() const { return x; }
};


void f(Point x)
{
    constexpr auto z = x.size();
    static_assert(z == 1, "");
}

int main()
{
    constexpr Point p;
    constexpr auto z = p.x;
    f(p);
}