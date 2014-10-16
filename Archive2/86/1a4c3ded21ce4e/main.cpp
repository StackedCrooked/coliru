#include <iostream>

template <typename U, typename T>
class params
{
    T m_value;

public:
    params(const T val)
        : m_value(val)
    {
    }
    
    bool check(int value) const
    {
        return (m_value + value) % 2;
    }
};

template <>
template <typename U>
bool params<U, long>::check(int value) const
{
    return (m_value * value) % 2;
}

int main()
{
    params<float, int> p1(3);
    std::cout << p1.check(5) << std::endl;
    
    params<float, long> p2(3);
    std::cout << p2.check(5) << std::endl;
}
