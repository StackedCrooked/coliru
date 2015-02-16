#include <mutex>
#include <boost/signals2/signal.hpp>
#include <iostream>

template<typename T>
auto acquire(T& lockable)
{
    return std::unique_lock<T>{lockable};
}

class A {
public:   
    int get_x() { 
        auto lock = acquire(_m); 
        return _x;
    }
    void set_x(int x) { 
        auto lock = acquire(_m);
        _x = x;
        _event();
    }
    boost::signals2::signal<void()>& get_event() {
        return _event;
    }
private:
    int _x = 42;
    boost::signals2::signal<void()> _event;
    std::recursive_mutex _m;
};

class C {
public:
    virtual void foo(A& a) = 0;
};

class D : public C {
public:
    virtual void foo(A& a) override { 
        std::cout << a.get_x(); 
    }
};

class B {
public:
    B(A& a, C& c) { 
        a._event.connect([&a, &c] { c.foo(a); });
    }
};

int main() {
    A a;
    D d;
    B b{a, d};
    a.set_x(1337);
}