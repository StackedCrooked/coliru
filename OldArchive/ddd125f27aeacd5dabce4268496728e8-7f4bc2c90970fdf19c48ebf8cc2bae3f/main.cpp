#include <cassert>
#include <algorithm>
#include <iostream>

template <typename T, int N> class SafeArray
{
public:
    SafeArray()
    {
        std::fill(m_data, m_data + N, false);
    }
    T &operator[](int index)
    {
        assert(0 <= index && index < N);
        return m_data[index];
    }
private:
    T m_data[N];
};

int main()
{
    SafeArray<bool, 3> b;
    for (int i = 0; i < 3; i++)
    {
        std::cout << b[i] << " ";
    }
}
