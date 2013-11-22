#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>
using namespace std;
#include <mutex>


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
/*
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
*/




template <class T>
struct dummy
{
    dummy(T& t): mt(t) { std::cout << " ..lock.. ";}
    ~dummy() { std::cout << " ..unlock.. ";}
    T& mt;
};

template <class T, class lockType> 
struct InnerWrapper
{
    InnerWrapper(T* t, unique_lock<lockType>& lock) : pT(t), lg(lock) {};
    T* operator->() { return pT;}
private: 
    T* pT;
    dummy<unique_lock<lockType>> lg;
};

template <class T, class lockType = std::mutex >
struct Monitor
{
public:
    Monitor(std::unique_ptr<T>&& _t) : t(move(_t)) {};
    InnerWrapper<T,lockType> operator->() {return InnerWrapper<T,lockType>(t.get(),lk);}
private:
    unique_lock<lockType> lk;
    std::unique_ptr<T> t;
};

struct Base
{    
    virtual ~Base(){};
    virtual void foo()=0;
};


struct Derived1 : public Base
{
    void foo(){cout << "Derived1::fooDo Something ";}
};

struct Derived2 : public Base
{
    void foo(){cout << "Derived2: Do Something ";}
};


int main()
{

    vector<Monitor<Base>> things;
    things.push_back(unique_ptr<Base>(new Derived1()));
    things.push_back(unique_ptr<Base>(new Derived2()));
    
    for (auto& thing : things)
        thing->foo();

  //  std::cout << wp->doSomething();
}
