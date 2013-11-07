#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>
using namespace std;


class SpinLock
{
public:
    SpinLock(){cout << " ..Lock spin.. " ;}
    ~SpinLock(){cout << " ..unLock spin.. ";}
};


class MutexLock
{
public:
    MutexLock(){cout << " ..Lock mutex.. " ;}
    ~MutexLock(){cout << " ..unLock mutex.. ";}
};

template<typename T>
class Prox
{
public:
    Prox(T* t) : pt(t)
    {
      cout << "|Intercept|" ;
    }
    ~Prox()
    {
        cout<< "|release|";
    }
    
    T* operator->()
    {
        return pt;
    }
    
    private:
    T* pt;
};

template<typename T, template <class> class Proxy >
class Mon2
{    
private:

       
public:
    Mon2(unique_ptr<T> _t): t(move(_t)){};
    Proxy<T> operator->()
    {
        return Proxy<T>(t.get());
    }
private:
    unique_ptr<T> t;
};


template<typename T, class lock = MutexLock>
class Monitor
{
    public:
    Monitor(unique_ptr<T> _t): t(move(_t)){};
    
    template <class F>
    typename result_of<F(T&)>::type Action(F f)
    {
        lock lk;
        return f(*t);
    }
private:
    unique_ptr<T> t;
};

struct bthing
{
    virtual char doSomething()=0;
};

struct thing : public bthing
{
    char doSomething(){cout << "Do Something "; return 'f';}
};

typedef Mon2<bthing, Prox> monitored_bThing;

struct tthing : public bthing
{
    char doSomething(){cout << "ttDo Something "; return 'b';}
};

int main()
{
    monitored_bThing m2(unique_ptr<bthing>(new tthing));
 
    auto g = m2->doSomething();
    
    cout << ": returned " << g;
}
