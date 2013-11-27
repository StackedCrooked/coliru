#include <iostream>

class Base
{   
public:    
    // "virtual" get method
    int get() const
    {
        return ((FPGet)(vtbl[class_index][get_index]))(*this);
    }
    
    // "virtual" set method
    void set(int x)
    {
        return ((FPSet)vtbl[class_index][set_index])(*this, x);
    }
    
private:
    typedef void (*FP)(); // basic function pointer used as common type
    typedef int(*FPGet)(const Base&); // getter method 
    typedef void(*FPSet)(Base&, int); // setter method
    
    enum
    {
        totalClasses = 2, // number of derived classes is hard coded!
        totalMethods = 2, // number of 'virtual' methods is hard coded!
        
        get_index = 0, // position for the 'get' method
        set_index = 1  // position for the 'set' method
    }; 
    
    // combined vtable for all methods of all subclasses    
    // it's a static member (so it's a global variable)
    // objects themselves are not burdened with vtables
    // 2-dimensional array layout provides very fast access
    static FP vtbl[totalClasses][totalMethods];
    
protected:
    // virtual methods are passed as function pointers to base class
    Base(uint8_t id, FPGet getter, FPSet setter) : class_index(id)
    {
        vtbl[class_index][0] = (FP)getter;
        vtbl[class_index][1] = (FP)setter;
    }  
    
private:
    uint8_t class_index; // class index
};


// initialize static
Base::FP Base::vtbl[Base::totalClasses][Base::totalMethods];


// Derived class
struct Test : Base
{
    enum { my_class_index = 0 };
    
    Test() : Base(my_class_index, &Test::do_get, &Test::do_set), n() // pass "virtual methods" as function pointers to static
    {
    }    

    static int do_get(const Base& b)
    {
        return static_cast<const Test&>(b).n;
    }
    
    static void do_set(Base& b, int n)
    {
        static_cast<Test&>(b).n = n;
    }
    
    int n;
};


int main()
{
    Test t;    
    t.set(2);
    std::cout << t.get() << std::endl;
}

