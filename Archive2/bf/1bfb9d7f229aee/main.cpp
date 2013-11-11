struct Point
{
    constexpr int size() const { return 1; }
};


void f(const Point &x)
{
    constexpr auto z = x.size();
    static_assert(z == 1, "");
}

int main()
{
    Point p;
    f(p);
}