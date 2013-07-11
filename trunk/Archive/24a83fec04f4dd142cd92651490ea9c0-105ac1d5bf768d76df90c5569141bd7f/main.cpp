#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <memory>

struct Parent{
    Parent(std::string){}
};

struct Child1 : public Parent{
    Child1(std::string d) : Parent(d){
        std::cout << "Child1 constructor: " << d << std::endl;
    }
};

struct Child2 : public Parent{
    Child2(std::string d) : Parent(d){
        std::cout << "Child2 constructor: " << d << std::endl;
    }
};

template <typename Product, typename Return, typename Parameter>
Return factory(const Parameter& a){
    return Return(new Product(a));
}

std::map<std::string, std::function<Parent*(std::string)> > mrp;
std::map<std::string, std::function<std::shared_ptr<Parent>(std::string)> > msp;

int main(){
    mrp["Child1"] = &factory<Child1, Parent*, std::string>;
    mrp["Child2"] = &factory<Child2, Parent*, std::string>;
    
    Parent* a = mrp["Child1"]("one");
    delete a;
    std::unique_ptr<Parent> b(mrp["Child2"]("two"));
    
    msp["Child1"] = &factory<Child1, std::shared_ptr<Parent>, std::string>;
    msp["Child2"] = &factory<Child2, std::shared_ptr<Parent>, std::string>;
    
    msp["Child1"]("one");
    msp["Child2"]("two");
}
