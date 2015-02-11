#include <iostream>

struct base
{
    virtual void name() const {std::cout << "Base\n"; }
    virtual ~base() = default;
};

struct derived: base
{
    virtual void name() const override {std::cout << "Derived\n"; }
    virtual ~derived() = default;
};

int main()
{
    base* b = new base; //b is a pointer to base;
    derived* d = new derived; //d is a pointer to derived
    base* arr[2]; //Array of two ponters to base
    arr[0] = b; //Assign b to first array element
    arr[1] = d; //Upcast pointer d to base* and assign it to second array element
    //arr[1] = static_cast<base*>(d); ← more clear
    for(auto p: arr) {
        p->name(); //virtual function call
        if(dynamic_cast<derived*>(p) != nullptr)  //Try to downcast pointer
            std::cout  << "Is derived\n";
        else
            std::cout << "Is not derived\n";
    }
}   