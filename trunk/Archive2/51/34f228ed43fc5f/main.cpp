#include <memory>
#include <iostream>
#include <unordered_map>
#include <cassert>

using namespace std;

template<class T>
struct MySharedFromThis {
    static unordered_map<T*, weak_ptr<T> > map;
    
    static std::shared_ptr<T> Find(T* p) {
        
        auto iter = map.find(p);
        
        if(iter == map.end())
            return nullptr;
        
        auto shared = iter->second.lock();
        
        if(shared == nullptr)
            throw bad_weak_ptr();
            
        return shared;
        
    }
};

template<class T>
unordered_map<T*, weak_ptr<T> > MySharedFromThis<T>::map;

template<class T>
struct MyDeleter
{
    void operator()(T * p)
    {
        std::cout << "deleter called" << std::endl;
        auto& map = MySharedFromThis<T>::map;
        
        auto iter = map.find(p);
        
        assert(iter != map.end());
        
        map.erase(iter);
        
        delete p;
    }
};

template<class T>
shared_ptr<T> MyMakeShared() {
    auto p = shared_ptr<T>(new T, MyDeleter<T>());
    MySharedFromThis<T>::map[p.get()] = p;
    return p;
}

struct Test {
    
    shared_ptr<Test> GetShared() { return MySharedFromThis<Test>::Find(this); }
    
};

int main()
{
    auto p = MyMakeShared<Test>();
    
    assert(p);
    assert(p->GetShared() == p);
    
}