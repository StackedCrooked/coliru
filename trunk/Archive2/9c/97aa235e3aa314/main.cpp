struct Y
{
    explicit Y(int) {}
};

struct X
{
    template <typename T> operator T() const
    {
        return T();
    }
    template operator Y() const = delete;
};

int main()
{
    X x;
    Y y(x); 
}
