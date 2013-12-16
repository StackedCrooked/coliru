#include <string>
#include <memory>
#include <utility>
#include <iostream>

template <typename T>
class Test
{
public:

    template <typename... Args>
    Test(Args&&... args)
    :  m_one(new T(args...)),
       m_two(new T(std::forward<Args>(args)...))    // <- Here
    {
    }

private:
    std::unique_ptr<T> m_one;
    std::unique_ptr<T> m_two;
};


class C
{ 
public:

    C(int a, int b, const std::string& c)
    :  m_a(a),
       m_b(b),
       m_c(c)
    {
        std::cout << "ctor a=" << m_a << ", b=" << m_b << ", c=" << m_c << "\n";
    }

    int m_a;
    int m_b;
    std::string m_c;
};


int main()
{
     Test<C> t(1, 2, "3");
}