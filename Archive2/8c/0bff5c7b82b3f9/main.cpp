#include <iostream>

template <typename T>
class Test
{
private:
    T m_t;
public:
    Test() { }
    explicit Test(const T &t) : m_t(t) { }
    T &GetValue() { return m_t; }
    const T &GetValue() const { return m_t; }
};

int main()
{
    int i;
    Test<int *> t(&i);
    i = 10;
    std::cout << *t.GetValue() << std::endl;
}