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
        return (m_value + value) % 2;
    }
};

template <>
template <typename D>
bool params<double>::check(D value) const
{
    return ((int)m_value + value) % 2;
}

int main()
{
    params<int> p1(2);
    p1.check(5);
    
    params<double> p2(4);
    p2.check(8);
}

