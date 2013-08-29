#include <iostream>
    
template<class Impl>
class StaticInterface  
{
public:
    void fun() const { static_cast<Impl const*>(this)->do_fun(); }
protected:
    ~StaticInterface() = default;
};

class StaticImpl: public StaticInterface<StaticImpl> // CRTP
{
private:
    friend StaticInterface<StaticImpl>;
    void do_fun() const { std::cout << "StaticImpl::do_fun()\n"; }
};

class DynamicInterface
{
public:
    void fun() const { do_fun(); }
protected:
    ~DynamicInterface() = default;    
private:
    virtual void do_fun() const = 0;
};

class DynamicImpl: public DynamicInterface
{
private:
    void do_fun() const override { std::cout << "DynamicImpl::do_fun()\n"; }
};

template<class Impl>
void abstr_fun(StaticInterface<Impl> const& s) { s.fun(); }
void concr_fun(StaticImpl            const& s) { s.fun(); }

void abstr_fun(DynamicInterface const& d) { d.fun(); }
void concr_fun(DynamicImpl      const& d) { d.fun(); }

int main()
{    
    StaticImpl s;
    abstr_fun(s);   // static binding
    concr_fun(s);   // static binding
    
    DynamicImpl d;
    abstr_fun(d);   // dynamic binding, except for optimization?
    concr_fun(d);   // dynamic binding, except for optimization?
}