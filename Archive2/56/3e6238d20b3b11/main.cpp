// transform algorithm example
#include <iostream>     // std::cout
#include <memory>
#include <type_traits>

template <typename T, bool IsPointer = false>
struct add_deep_const_impl;

template <typename T>
struct add_deep_const_impl<T, false>
{
    typedef const T type;
};

template <typename T>
struct add_deep_const_impl<T, true>
{
    typedef std::add_pointer_t<typename add_deep_const_impl<std::remove_pointer_t<T>, std::is_pointer<std::remove_pointer_t<T>>::value>::type> const type;
};

template <typename T>
struct add_deep_const : add_deep_const_impl<T, std::is_pointer<T>::value>
{
};



template <typename T>
class deep_constness_ptr {
    
public:
    deep_constness_ptr(T* raw) : raw(raw){}
    
    typename add_deep_const<T*>::type get() const {return raw;}
    T* get() {return raw;}
    
    operator typename add_deep_const<T*>::type() const {return raw;}
    operator T*() {return raw;}
    
    typename add_deep_const<T*>::type operator ->() const {return raw;}
    T* operator ->()  {return raw;}
    
    typename add_deep_const<T>::type& operator *() const {return *(const_cast<typename add_deep_const<T*>::type>(raw));}
    T& operator *() {return *raw;}
                
private:
    T* raw;    
};


class Bar {
public:
    int*** i;
};

class Foo {
public:
    deep_constness_ptr<int**> i;
};

int main () {
    
    int*** p = new int**{new int*{new int{5}}};
    
    //============================
    
    Bar bar{p};
    ***bar.i = 7; // OK
    
    const Bar cbar {p};
    ***cbar.i = 8; // OK
    
    //============================
    
    Foo foo{p};
    ***foo.i = 7; // OK
    
    const Foo cfoo {p};
    //***cfoo.i = 8; //error
        
  
    return 0;
}
