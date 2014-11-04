#include <iostream>
#include <unordered_map>
#include <functional>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/construct.hpp>

using Opcode = int;

class Operation {
public:
    virtual ~Operation() {}
    virtual void print() = 0;
};

class OperationFoo: public Operation {
public:
    virtual void print() { std::cout << "OperationFoo" << std::endl; }
};

class OperationBar: public Operation {
public:
    virtual void print() { std::cout << "OperationBar" << std::endl; }
};

class OperationQux: public Operation {
public:
    virtual void print() { std::cout << "OperationQux" << std::endl; }
};

int main()
{    
    std::unordered_map<Opcode, std::function<Operation *()>> factory {
        { 1, boost::lambda::new_ptr<OperationFoo>() },
        { 2, boost::lambda::new_ptr<OperationBar>() },
        { 3, boost::lambda::new_ptr<OperationQux>() },
    };
    
    Operation* a = factory[1](); a->print();
    Operation* b = factory[2](); b->print();
    Operation* c = factory[3](); c->print();
    
    delete a; delete b; delete c;
}
