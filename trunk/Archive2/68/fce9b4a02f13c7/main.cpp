#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

using PyObject = void;

PyObject* PyObject_GetItem( PyObject* pyob, PyObject* key ) { cout << "In PyObject_GetItem \n"; return nullptr; }
void PyObject_SetItem( PyObject* pyob, PyObject* key, PyObject* value ) { cout << "In PyObject_SetItem \n"; }

class Object {
public:
    PyObject* p;
    //Object& memberOb;
    
    Object(PyObject* _p) : p{_p} {}
    
    void someMethod() { cout << "In someMethod() \n"; }
    //PyObject* ptr() { cout << "In ptr() \n"; return p; }
    
    const Object operator[] (const Object& key)  const { 
        return Object{ PyObject_GetItem( p, key.p ) }; 
    }

    class Proxy {
    private:
        const Object& container;
        const Object& key;
    
    public:
        // at this moment we don't know whether it is 'c[k] = x' or 'x = c[k]'
        Proxy( const Object& c, const Object& k ) : container{c}, key{k}
        { }
    
        // Rvalue
        // e.g. cout << myList[5] hits 'const Object operator[]'
        operator Object() const {
            return container[key];
        }
    
        // Lvalue
        // e.g. (something = ) myList[5] = foo
        const Proxy&  operator= (const Object& rhs_ob) {
            PyObject_SetItem( container.p, key.p, rhs_ob.p );
            return *this; // allow daisy-chaining a = b = c etc, that's why we return const Object&
        }
    
        const Object* operator->() const { return &container[key]; }
        // ^ ERROR: taking the address of a temporary object of type Object
        
        Object operator->() { return container[key]; }
    };
    
    const Object* operator -> () const { return this; }
    Object* operator -> () { return this; }        
};

int main()
{
    Object ob{}, idx{}, idx2{}, target{};
    ob[idx] = ob[idx2] = target{};
    ob[idx].someMethod();
    //ob[idx].memberOb = Object{};
    PyObject* w = ob[idx]->p;
} 
