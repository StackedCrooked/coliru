#include <utility>
#include <cstdio>
#include <type_traits>

template <typename T = void>
class SuperClass
{
    using CRTP = typename std::conditional<std::is_same<T, void>::value, SuperClass, T>::type;
    
public:
    CRTP& SetA(int a)
    {
        m_a = a;
        return static_cast<CRTP&>(*this);
    }
    
    virtual void Print()
    {
        printf("a=%i\n", m_a);
    }
protected:
    int m_a;
};

class SubClass : public SuperClass<SubClass>
{
public:
    SubClass& SetB(double b)
    {
        m_b = b;
        return *this;
    }
    virtual void Print()
    {
        printf("a=%i, b=%f\n", m_a, m_b);
    }
protected:
    double m_b;
};

int main()
{
    SubClass().SetB(123.4).SetA(123).Print();
    SubClass().SetA(123).SetB(123.4).Print();
    SuperClass<>().SetA(123).Print();
    
    using SuperClass_t = SuperClass<>;
    SuperClass_t().SetA(123).Print();
    
}
