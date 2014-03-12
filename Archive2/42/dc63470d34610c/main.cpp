#include <iostream>
#include <string>
#include <vector>

class A {
public:
    virtual ~A() = 0;
};

class B:
    public A
{
};

template <class T_> class D;

D<int> *d0;

class C {

    
};


template <class T_>
class D {
    
};

D<int> d;

template<class T_>
class hdl_tree_node; // !

template <
    class T_
> class hdl_tree_node_descriptor {
public:
    virtual ~hdl_tree_node_descriptor() {
    }


private:
    T_ metadata_;
    hdl_tree_node *p_;
};

template<class T_>
class hdl_tree_node {
    
};


int main()
{

    
    
    return 0;
}

