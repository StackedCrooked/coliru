#include <utility>
#include <cstdio>

template <bool b, typename T, typename F>
struct conditional
{
    typedef F type;
};

template <typename T, typename F>
struct conditional<true, T, F>
{
    typedef T type;
};

template <typename T, typename U>
struct is_same
{
    static const bool value = false;
};

template <typename T>
struct is_same<T, T>
{
    static const bool value = true;
};

template <typename T = void>
class SuperClassCRTP
{
    typedef typename conditional<is_same<T, void>::value, SuperClassCRTP, T>::type CRTP;
    
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

class SubClass : public SuperClassCRTP<SubClass>
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

typedef SuperClassCRTP<> SuperClass;

int main()
{
    SubClass().SetB(123.4).SetA(123).Print();
    SubClass().SetA(123).SetB(123.4).Print();
    SuperClass().SetA(123).Print();    
}
