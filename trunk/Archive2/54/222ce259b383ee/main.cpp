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
using unique_ptr_default = unique_ptr<T, default_delete<T>>;




template <typename T>
class RefStoragePolicy
{
public:
    RefStoragePolicy(T& _t) : t(&_t){};
    RefStoragePolicy(T* _t) : t(_t){};
    RefStoragePolicy(const RefStoragePolicy<T>& other) = delete;
    RefStoragePolicy(RefStoragePolicy<T>&& other) : t(other.t) {
        other.t = nullptr;
        };
    T* get() {
        return t;
    }
private:
    
    T* t;
};

template <class T>
RefStoragePolicy<T> WrapInRefPolicy(T* t) {
    return RefStoragePolicy<T>(t);
}




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

template <class T, template <class> class storage =unique_ptr_default , class lockType = std::mutex >
struct Monitor
{
public:
    Monitor(const storage<T>& _t) : t(_t) {};
    Monitor(storage<T>&& _t) : t(move(_t)) {};
    InnerWrapper<T,lockType> operator->() {return InnerWrapper<T,lockType>(t.get(),lk);}
private:
    unique_lock<lockType> lk;
    storage<T> t;
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



void Func(shared_ptr<Base> thing)
{
    Monitor<Base,shared_ptr> wrappedThing(move(thing));
    wrappedThing->foo();
}

template <class T>
Monitor<T,RefStoragePolicy> MakeMonitor(T* t) {
    return Monitor<T,RefStoragePolicy>(t);
}

template <class T>
Monitor<T,RefStoragePolicy> MakeMonitor(const T& t) {
    return Monitor<T,RefStoragePolicy>(t);
}



template <class T, template <class> class smartPtrType>
auto MakeMonitor(const smartPtrType<T>& t) -> decltype(t.get(), Monitor<T,smartPtrType>(t)) {
    return Monitor<T,smartPtrType>(t);
}

template <class T>
Monitor<T,unique_ptr_default> MakeMonitor(unique_ptr<T>&& t) {
    return Monitor<T,unique_ptr_default>(move(t));
}


int main()
{
 //   typedef Monitor<Base,unique_ptr_def> MonBase;
 //   typedef Monitor<Base,shared_ptr> MonBase;
  //  vector<MonBase> things;
 //   things.push_back(MonBase(shared_ptr<Base>(new Derived1())));
 //   things.push_back(MonBase(shared_ptr<Base>(new Derived2())));
    
    
    Monitor<Base,unique_ptr_default> mon1(unique_ptr<Base>(new Derived1()));
    Monitor<Base> mon2(unique_ptr<Base>(new Derived1()));
    
 //  for (auto& thing : things)
  //      thing->foo();


   Derived1 derived;
   auto wrapped = RefStoragePolicy<Derived1>(&derived);
   auto wrappedEasier = WrapInRefPolicy(&derived);
   wrapped.get();
   wrappedEasier.get();
   
  // Derived1* pDerived = &derived;
   /*
   Monitor<Base,RefStoragePolicy> monitor1(derived);
   Monitor<Base,RefStoragePolicy> monitor2(pDerived);
   
   auto monitor3 = MakeMonitor(&derived);
   auto monitor4 = MakeMonitor(derived);
   */
   shared_ptr<Base> p(new Derived1());
   auto monitor5 = MakeMonitor(p);
   monitor5->foo();
   
   unique_ptr<Base> p1(new Derived1());
   auto monitor6 = MakeMonitor(move(p1));
   auto monitor7 = MakeMonitor(unique_ptr<Base>(new Derived1()));
   monitor6->foo();
   monitor7->foo();
 //  monitor1->foo(); 
  // monitor2->foo();
  // monitor3->foo();
   
   //shared_ptr<Base> shrd(new Derived1());
   //Func(shrd);
    //Func(shrd);
  //  std::cout << wp->doSomething();
}
