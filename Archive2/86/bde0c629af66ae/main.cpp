#include <iostream>
#include <string>

template<class T>
class cyclic_buffer
{
private:
    size_t  m_size;
    size_t  m_current;
    size_t  m_taken;
    T*      m_elements;
    
public:
    cyclic_buffer(size_t size)
    {
        m_size      = size;
        m_current   = 0U;
        m_taken     = 0U;
        
        m_elements  = new T[size];
    }
    
    ~cyclic_buffer()
    {
        delete[] m_elements;   
    }
    
    void add(T&& value)
    {
        m_elements[m_current] = std::move(value);
        
        m_current = (m_current + 1U) % m_size;
        
        if (m_taken < m_size)
            m_taken += 1U;
    }
    
    template<class TFunc>
    void for_each(TFunc&& fn)
    {
        size_t start = 0U;
        if (m_taken == m_size)
            start = m_current;
            
        for (size_t i = start; i < m_size; ++i)
            fn(m_elements[i]);
            
        if (start != 0U)
        {
            for (size_t i = 0; i < start; ++i)
                fn(m_elements[i]);
        }
    }
};

int main()
{
    auto buf = cyclic_buffer<std::string>(4);
    
    std::string s1 = "abc";
    std::string s2 = "def";
    std::string s3 = "ghi";
    std::string s4 = "jkl";
    std::string s5 = "mno";
    std::string s6 = "ahoj";
    
    buf.add(std::move(s1));
    buf.add(std::move(s2));
    buf.add(std::move(s3));
    buf.add(std::move(s4));
    buf.add(std::move(s5));
    buf.add(std::move(s6));
    
    buf.for_each([](const std::string& str) { std::cout << str << std::endl; });
    
    return 0;
}