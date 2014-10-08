#include <iostream>
#include <memory>
#include <vector>


    
    
    
class Protocol
{   
public: 
    void pop(int x)
    {
        // lookup the function pointer in the 2-d array
        return ((FPPop)(vtbl[class_id_][pop_index]))(*this, x);
    }
    
    void push()
    {
        // lookup the function pointer in the 2-d array
        return ((FPPush)vtbl[class_id_][push_index])(*this);
    }
    
private:
    typedef void (*FP)(); // basic function pointer used as common type
    typedef void(*FPPush)(Protocol&); // fppop method 
    typedef void(*FPPop)(Protocol&, int); // fppush method
    
    enum
    {
        totalClasses = 2, // number of derived classes is hard coded!
        totalMethods = 2, // number of 'virtual' methods is hard coded!
        
        pop_index  = 0, // position for the 'get' method
        push_index = 1  // position for the 'set' method
    };
    
    // combined vtable for all methods of all subclasses    
    // it's a static member (so it's a global variable)
    // BasicProtocols themselves are not burdened with vtables
    // 2-dimensional array layout provides very fast access
    static FP vtbl[totalClasses][totalMethods];
    
protected:

    // virtual methods are passed as function pointers to Protocol class
    Protocol(int class_id, FPPop fppop, FPPush fppush) : class_id_(class_id)
    {
        vtbl[class_id][pop_index ] = reinterpret_cast<FP>(fppop);
        vtbl[class_id][push_index] = reinterpret_cast<FP>(fppush);
    }  
    
private:
    uint8_t class_id_; // class index
};

Protocol::FP Protocol::vtbl[Protocol::totalClasses][Protocol::totalMethods];



// Derived class
template<typename T>
struct BasicProtocol : Protocol
{        
    BasicProtocol(int class_id) : Protocol(class_id, &BasicProtocol::do_pop, &BasicProtocol::do_push)
    {
    }

    static void do_push(Protocol& Protocol)
    {
        return static_cast<T&>(Protocol).push();
    }
    
    static void do_pop(Protocol& Protocol, int n)
    {
        static_cast<T&>(Protocol).pop(n);
    }
};



// Derived class
struct IPv4Protocol : BasicProtocol<IPv4Protocol>
{
    enum { class_id = 0 };
    IPv4Protocol() : BasicProtocol(class_id), n_()
    {
    }

    void push()
    {
        std::cout << "IPv4Protocol::push\n";
    }
    
    void pop(int n)
    {
        std::cout << "IPv4Protocol::pop\n";
        n_ = n;
    }
    
    int n_ = 0;
};



// Derived class
struct IPv6Protocol : BasicProtocol<IPv6Protocol>
{
    enum { class_id = 1 };
    
    IPv6Protocol() : BasicProtocol(class_id), n_()
    {
    }

    void push()
    {
        std::cout << "IPv6Protocol::push\n";
    }
    
    void pop(int n)
    {
        std::cout << "IPv6Protocol::pop\n";
        n_ = n;
    }
    
    int n_ = 0;
};


int main()
{
    std::vector<std::unique_ptr<Protocol>> protocols;
    protocols.push_back(std::make_unique<IPv4Protocol>());
    protocols.push_back(std::make_unique<IPv6Protocol>());
    
    for (auto&& protocol : protocols)
    {
        protocol->pop(1);
        protocol->push();
    }
}

