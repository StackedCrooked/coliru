#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Base {
public:
    std::string Name;
};
using BaseList = std::vector<std::shared_ptr<Base>>;

class Derived : public Base {
public:
    std::string DerivedName = "Derived";
    
};
using DerivedList = std::vector<std::shared_ptr<Derived>>;

class BaseHandler {
public:
    void process( BaseList list ) {
         std::cout << "process " << list[0]->Name  << std::endl;
    }
};

class BaseForwarder {
public:

    template <class T,
            class SharedPtr = typename T::value_type,
            class Element = typename SharedPtr::element_type,
            class IsDerived = typename std::enable_if<std::is_base_of<Base, Element>::value, void*>::type
        >
    void process(const T& t) { 
        BaseHandler bh;
        bh.process(t);
    }

};


int main() {
 
    DerivedList list;
    Derived item;
    item.Name = "Test";
    list.push_back( std::make_shared<Derived>(item) );
 
    BaseForwarder bf;
    bf.process( list );
     
}