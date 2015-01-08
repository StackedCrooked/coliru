#include <iostream>

template <typename T> 
class foo
{
private:
    T m_var;
public:
    foo(T init_var)
    {
        m_var = init_var;
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

template<>
foo<int>::foo(int init_var)
{
    m_var = init_var + 1;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    foo<int>(3); // foo1.m_var is 4
    foo<char>('a'); // foo2.m_var is a
}
