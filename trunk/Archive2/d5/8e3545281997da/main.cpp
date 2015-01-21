#include <memory>
#include <iostream>
#include <unordered_map>
#include <cassert>

using namespace std;

template<class T>
struct Holder {
    weak_ptr<T> weak;
    T value;
};

template<class T>
Holder<T>* GetHolder(T* p) {
    
    // Scary!
    auto h = reinterpret_cast< Holder<T>* >(reinterpret_cast<char*>(p) - sizeof(weak_ptr<T>));
    
    cout << "GetHolder returning " << h << endl;
    
    return h;
    
}

template<class T>
struct MyDeleter
{
    void operator()(T * p)
    {
        cout << "deleter called" << endl;
        
        delete GetHolder(p);
    }
};

template<class T>
shared_ptr<T> MyMakeShared() {
    auto holder = new Holder<T>;
    cout << "Holder at " << holder << std::endl;
    auto p = shared_ptr<T>(&(holder->value), MyDeleter<T>());
    holder->weak = p;
    return p;
}

template<class T>
shared_ptr<T> MySharedFromThis(T* self) {
    return GetHolder(self)->weak.lock();
}

struct Test {
    
    shared_ptr<Test> GetShared() { return MySharedFromThis(this); }
    
};

int main()
{
    auto p = MyMakeShared<Test>();
    
    assert(p);
    assert(p->GetShared() == p);
    
}