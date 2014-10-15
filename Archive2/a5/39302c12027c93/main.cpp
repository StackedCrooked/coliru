struct I
{
    explicit I(int val) : m_value(val) {}

    int m_value;
};

template <typename T>
class params
{
    T m_value;

public:
    params(const T val)
        : m_value(val)
    {
    }

    template <typename D>
    bool check(D value) const
    {
        return (value) % 2;
    }
};

template <>
template <typename D>
bool params<I>::check(D value) const
{
    return (value) % 2;
}

int main()
{
    params<int> p1(2);
    p1.check(5);
    
    params<I> p2(I(4));
    p2.check(8);
}

