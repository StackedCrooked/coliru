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



template<typename T, class lock = MutexLock>
class Mon2
{    
public:
    Mon2(unique_ptr<T> _t): t(move(_t)){};
    T* operator->()
    {
         lock lk;
         return t.get();
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

struct tthing : public bthing
{
    char doSomething(){cout << "ttDo Something "; return 'b';}
};

int main()
{
    tthing tt;
    Monitor<bthing, SpinLock> wT(unique_ptr<bthing>(new tthing));
     auto g =  wT.Action([](bthing& t){return t.doSomething();});
  //  Mon2<bthing, SpinLock> m2(unique_ptr<bthing>(new tthing));
//    auto g = m2->doSomething();
    cout << g;
}
