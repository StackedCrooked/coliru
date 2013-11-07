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
    ~SpinLock(){cout << " ..unLock spin..\n ";}
};


class MutexLock
{
public:
    MutexLock(){cout << " ..Lock mutex.. " ;}
    ~MutexLock(){cout << " ..unLock mutex..\n ";}
};


template<class lk, typename T>
class GenProx
{
public:
    GenProx(T* t) : pt(t)
    {}
    
    T* operator->()
    {
        return pt;
    }
    
private:
    T* pt;
    lk sp;
};


template<typename T, typename lock>
class Mon2
{
public:
    Mon2(unique_ptr<T> _t): t(move(_t)){};
    GenProx<lock,T> operator->()
    {
        return GenProx<lock, T>(t.get());
    }
    T* release(){return t.release();}
private:
    unique_ptr<T> t;
};


template <class T>
using unique_ptr_def = unique_ptr<T, default_delete<T>>;

template <typename T>
class Store
{
    public:
    
    Store(T& _t) : t(_t){};
    T* operator->()
    {
        return &t;
    }
    operator T& ()
    {
        return t;
    }
    
    T& operator * ()
    {
        return t;
    }
private:
    
    T& t;
};

template<typename T,  template <class> class storage = unique_ptr_def, class lock = MutexLock>
class Monitor
{
    public:
    Monitor(storage<T> _t): t(move(_t)){};
    
    template <class F>
    auto Action(F f) -> typename result_of<F(T&)>::type
    {
        lock lk;
        return f(*t);
    }
private:
    storage<T> t;
};

struct bthing
{
    bthing()
    {
        cout << "Bthing created";
    }
    
    virtual ~bthing()
    {
        cout << "Bthing killed";
    }
    virtual char doSomething()=0;
};

struct thing : public bthing
{
    char doSomething(){cout << "Do Something "; return 'f';}
};

typedef Mon2<bthing, MutexLock> monitored_bThing;

struct tthing : public bthing
{
    char doSomething(){cout << "ttDo Something "; return 'b';}
};

int main()
{
    unique_ptr<bthing> ddd(new tthing);
   /// ddd->doSomething();
     
    monitored_bThing m2(move(ddd));
 
    auto g = m2->doSomething();
    ddd.reset(m2.release());
    
    tthing stackOb;
    
  ///  ddd->doSomething();
    Monitor<bthing,Store> mon(stackOb);
    mon.Action([](bthing& t){return t.doSomething();});
        
    cout << ": returned " << g;
}
