#include <iostream>
#include <string>
#include <vector>

template<typename T>
class Foo {
    public:
    Foo() :z(0) {}
  
    template <typename U>
    typename std::enable_if<!std::is_integral<U>::value && 
                            std::is_same<T, U>::value, void>::type
    f(const Foo<U>& x)
    {
        z = x.z;
        std::cout << "First function called \n Value = " << z << std::endl; 
    }
    
    template <typename U>
    typename std::enable_if<std::is_integral<U>::value && 
                            std::is_same<T, U>::value, void>::type
    f(const Foo<U>& x)
    {
        z = x.z;
        std::cout << "Second function called \n Value = " << z << std::endl; 
        
    }
    
    template <typename U>
    typename std::enable_if<!std::is_same<T, U>::value, void>::type
    f(const Foo<U>& x)
    {
        z = x.z;
        std::cout << "Default function called \n Value = " << z << std::endl; 
        
    }
    

  T z;
};

template<typename T>
class WeakRef {
    public:
    WeakRef(){}
    
    template<typename U>
    typename std::enable_if<std::is_same<T,U>::value, WeakRef<T>& >::type
    operator = (const U& other){
        std::cout << "Same types go here - value = " << other << std::endl;
        return (*this);
    }
    
    template<typename U>
    typename std::enable_if<!std::is_same<T,U>::value && std::is_base_of<T,U>::value, WeakRef<T>& >::type
    operator = (const U& other){
        std::cout << "If U is derived from T this executes with val = " << other << std::endl;
        return (*this);
    }
    
    template<typename U>
    typename std::enable_if<!std::is_same<T,U>::value && !std::is_base_of<T,U>::value, WeakRef<T>& >::type
    operator = (const U& other){
        std::cout << "Unrelated types go here" << std::endl; 
        std::cout << "and we hope they have a custom assignment op " << std::endl;
        std::cout << "also the value is " << other << std::endl;
        return (*this);
    }
    
    
    
};

class Base{};
class Derived : public Base {
    public:
    float value;
};

std::ostream & operator << (std::ostream& stream, const Derived& x){
    stream << "Derived object of value " << x.value << std::endl;
    return stream;
}

std::ostream & operator << (std::ostream& stream, const Base& x){
    stream << "Base object encountered !"<< std::endl;
    return stream;
}


int main(){
    
    
    
    Foo<int> int_foo;
    int_foo.z = 777;
    Foo<double> db_foo;
    db_foo.z = 3.03;

    Foo<unsigned char> char_foo;
    char_foo.f(int_foo);
    
    Foo<float> float_foo;
    float_foo.f(db_foo);
    
    Foo<int> copy_foo;
    copy_foo.f(int_foo);
    Foo<float> copy_float;
    copy_float.f(float_foo);
    
    
    WeakRef<float> float_ref;
    
    float_ref = 0.0f;
    float_ref = 3;
    float_ref = 2.0;
    
    WeakRef<Base> base_ref;
    
    Base b;
    Derived d;
    d.value = 1792.0f;
    
    
    base_ref = b;
    base_ref = d;
    
    
    return 0;
}
