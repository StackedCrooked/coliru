#include <iostream>
#include <vector>

template <typename T>
struct AutoVector
{
    std::vector<T> m_vec;
    AutoVector() { m_vec.resize(1); }
    
    T& operator[](const size_t index) &
    {
        std::cout << "Inside operator[" << index << "]&\n";
        if (m_vec.size() < index)
            m_vec.resize(index);
        return m_vec[index];
    }
    
    T operator[](const size_t index) &&
    {
        std::cout << "Inside operator[" << index << "]&&\n";
        return m_vec[index];
    }
};

int main()
{
    AutoVector<int> avec;
    
    avec[4] = 6;
    std::cout << avec[4] << "\n";
    
    std::cout << "\n";
    std::cout << AutoVector<int>()[0] << "\n";
}
