#include <iostream>

template<class __derived>
struct Base_traits {
    //using Object = ?????;
};

template < class __derived, class __object = typename Base_traits<__derived>::Object >
struct Base {
    using Derived = __derived;
    using Object = typename Base_traits<__derived>::Object;
    void foo(Object o) { self()->bar(o); }
private:
    __derived* self() {return static_cast<__derived*>(this);}
    const __derived* self() const {return static_cast<__derived*>(this);}
};



template < class __object >
struct Derived : public Base< Derived< __object > > {
    using Object = __object;
    void bar(Object o) { 
        std::cout << o;
    }
};
template<class __object>
struct Base_traits<Derived<__object>> {
    using Object = __object;
};



int main() {
    Derived<int> a;
    a.foo(3);
}