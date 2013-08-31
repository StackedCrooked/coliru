
#include <set>
#include <functional>
#include <memory>

template<typename T>
class Notified {
    T v;
    
    using CbType = std::function<void(const T&)>;
    
    std::set<std::unique_ptr<CbType>> cbs;
    
    void _notify() { for (auto & cb : cbs) (*cb)(v); }
    
public:
    template<class Cb>
    void addCallback(Cb&& cb) { cbs.insert(std::unique_ptr<CbType>(new CbType(cb))); }

    T& operator=(const T& rhs) { v = rhs; _notify(); return v; }
    T& operator=(T&& rhs) { v = std::move(rhs); _notify(); return v; }
    
    Notified(const T& rhs) : v(rhs) { }
    Notified(T&& rhs) : v(std::move(rhs)) { }
    
    operator T () { return v; }
};



#include <iostream>
using namespace std;

void foo(int i) { cout << "foo : " << i << "\n"; }

int main () {
    
    Notified<int> i (5);
    
    cout << "cout :" << i << "\n";
    foo(i);
    
    i.addCallback([](int i){ cout << "lambda :" << i << "\n"; });
    
    i = 3;
    foo(i);
}