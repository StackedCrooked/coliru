#include <iostream>
#include <string>
#include <vector>
#include <functional>

template<class Fun>
struct base
{
    virtual const void* get() const = 0;
    virtual void assign(const void* p) = 0;
    virtual void dump(std::ostream&) const = 0;
    virtual void call() = 0;
};

template<class T, class Fun>
struct wrap : base<Fun>
{
    T t;
    virtual const void* get() const { return &t; }
    virtual void assign(const void* p) { t = *static_cast<const T*>(p); }
    virtual void dump(std::ostream& os) const { os << t; }
    virtual void call() { Fun()(t); }
};

template<class Fun>
struct any
{
    base<Fun>* ptr;
    
    template<class T>
    any(const T& t) : ptr(new wrap<T>) { ptr->assign(&t); }
    
    template<class T>
    any& operator= (const T& t) { ptr->assign(&t); return *this;}

    template<class T>
    T cast() const { return *static_cast<T*>(ptr->get()); }
    
    void dump(std::ostream& os) { ptr->dump(os); }
};

int main()
{
    any a{1};
    a.dump(std::cout);
    a = 2;
    a.dump(std::cout);
}
