#include <iostream>

class Base
{
    typedef void (*FP)();
    typedef int(*FPGet)(const Base&);
    typedef void(*FPSet)(Base&, int);
    
    enum 
    {
        totalClasses = 2,
        totalMethods = 2
    };
    static FP vtbl[totalClasses][totalMethods];
    uint8_t tag;
    
protected:
    Base(uint8_t n, FPGet getter, FPSet setter) : tag(n)
    {
        vtbl[tag][0] = (FP)getter;
        vtbl[tag][1] = (FP)setter;
    }
    
public:
    int get() const
    {
        return ((FPGet)(vtbl[tag][0]))(*this);
    }
    
    void set(int x)
    {
        return ((FPSet)vtbl[tag][1])(*this, x);
    }
};


Base::FP Base::vtbl[Base::totalClasses][Base::totalMethods];


struct SendCounter : Base
{
    SendCounter() : Base(0, &SendCounter::do_get, &SendCounter::do_set), n()
    {
    }
    

    static int do_get(const Base& b)
    {
        return static_cast<const SendCounter&>(b).n;
    }
    
    static void do_set(Base& b, int n)
    {
        static_cast<SendCounter&>(b).n = n;
    }
    
    int n;
};


struct ReceiveCounter : Base
{
    ReceiveCounter() : Base(1, &ReceiveCounter::do_get, &ReceiveCounter::do_set), n()
    {
    }
    

    static int do_get(const Base& b)
    {
        return static_cast<const ReceiveCounter&>(b).n;
    }
    
    static void do_set(Base& b, int n)
    {
        static_cast<ReceiveCounter&>(b).n = n;
    }
    
    int n;
};


int main()
{
    SendCounter t;    
    t.set(2);
    std::cout << t.get() << std::endl;
    
    ReceiveCounter r;    
    r.set(4);
    std::cout << r.get() << std::endl;
}

