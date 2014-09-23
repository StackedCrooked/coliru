#include <cstdio>

template<class T>
class SuperClass {
public:
    T& SetA(int a) {
        m_a = a;
        return *dynamic_cast<T*>(this);
    }
    virtual void Print() {
        printf("a=%i", m_a);
    }
protected:
    int m_a;
};
class SubClass : public SuperClass<SubClass>
{
public:
    SubClass& SetB(double b) {
        m_b = b;
        return *this;
    }
    virtual void Print() {
        printf("a=%i, b=%f", m_a, m_b);
    }
protected:
    double m_b;
};

int main(int argc, char* argv[])
{
    SubClass().SetB(123.4).SetA(123).Print();       // Works fine
    SubClass().SetA(123).SetB(123.4).Print();       // Failed
}