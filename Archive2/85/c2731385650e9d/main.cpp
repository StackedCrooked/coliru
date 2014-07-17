#include <vector>
#include <memory>
#include <iostream>


class VirtualBase {  // Really am not sure what it should be called, sorry
    class Interface {
    public:
        virtual double get() = 0;
    };
    
    template<typename T>
    class Impl : public Interface {
        T m_impl_obj;
        
    public:
        Impl(T impl_obj) : m_impl_obj(std::move(impl_obj)) {}
        
        double get() override {
            return m_impl_obj.get();
        }
    };

    std::shared_ptr<Interface> m_obj;

public:
    template<typename T>
    VirtualBase(T obj) : m_obj(new Impl<T>(std::move(obj))) {}

    double get() {
        return m_obj->get();
    }
};


template <typename Derived>
class Base{
public:
    double get(){
        return static_cast<Derived*>(this)->implementation();
    }
};

class DerivedA : public Base<DerivedA>{
public:
    double get(){ return 2.0;}
};

class DerivedB : public Base<DerivedB>{
public:
    double get(){ return 1.0;}
};


int main() {
    std::vector<VirtualBase> v;
    v.emplace_back(DerivedA{});
    v.emplace_back(DerivedB{});
    
    for(auto b : v) {
        std::cout << b.get() << std::endl;
    }
}