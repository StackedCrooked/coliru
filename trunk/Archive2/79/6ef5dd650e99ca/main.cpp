#include <iostream>

template<class H>
class Arithmetic{   //interface
public:
    H& operator++()
    {
        H* ph = static_cast<H*>(this);
        ph->inc(1);
        return *ph;
    }

    H& operator+=(int n)
    {
        H* ph = static_cast<H*>(this);
        ph->inc(n);
        return *ph;
    }

    H operator++(int n)
    {
        H* ph = static_cast<H*>(this);
        H tmp = *ph;
        ph->inc(n);
        return tmp;
    }

    friend H operator+(const H& lhs, const H& rhs){
        return H(lhs.get()+rhs.get());
    }
};

class Integer : public Arithmetic< Integer >
{
public:
    Integer(int a):m_(a){}
    Integer(const Integer& t):m_(t.m_){}
    void inc(int n){ //depended implementation. flexed changed.
        m_+=n;
    }
    int get() const{ return m_;}
private:
    int m_;
};

int main(){
    
    Integer a(10);
    ++a;
    a++;
    a+=3;
    Integer b(10);

    Integer c = a + b;
    std::cout<< "result is :" << c.get() << std::endl;
}


