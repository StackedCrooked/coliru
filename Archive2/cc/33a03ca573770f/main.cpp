#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

using PyObject = int;

PyObject* PyObject_GetItem( PyObject* pyob, PyObject* key )                  { cout << "PyObject_GetItem \n"; return nullptr; }
void      PyObject_SetItem( PyObject* pyob, PyObject* key, PyObject* value ) { cout << "PyObject_SetItem \n"; }

class Object {
public:
    PyObject* p;
    //Object& memberOb;
    
    Object(PyObject* _p) : p{_p} { cout << "Constructing " << (p==nullptr?0:*p) << " \n"; }
    
    void someMethod() { cout << "In someMethod() \n"; }
    //PyObject* ptr() { cout << "In ptr() \n"; return p; }
    
    const Object operator[] (const Object& key)  const { 
        cout << "const Object operator[] \n";
        return Object{ PyObject_GetItem( p, key.p ) }; 
    }

    Object& operator= (const Object& rhs) {
        cout << "const Object& operator= \n";
        p = rhs.p;
        return *this;
    }

    class Proxy {
    private:
        PyObject* container;
        PyObject* key;
        
        //Object value{};
    
    public:
        // at this moment we don't know whether it is 'c[k] = x' or 'x = c[k]'
        Proxy( PyObject* c, PyObject* k ) : container{c}, key{k} { 
            cout << "Proxy::constructor \n"; 
        }
    
        // Rvalue
        // e.g. cout << myList[5] hits 'const Object operator[]'
        operator Object() const {
            cout << "Proxy::operator Object() const \n"; 
            return Object{ PyObject_GetItem(container,key) };
        }
    
        // Lvalue
        // e.g. (something = ) myList[5] = foo
        Proxy&  operator= (const Object& rhs_ob) {
            cout << "Proxy::const Proxy&  operator= \n"; 
            
            PyObject_SetItem( container, key, rhs_ob.p );
            return *this; // allow daisy-chaining a = b = c etc, that's why we return const Object&
        }

        Proxy&  operator= (const Proxy& rhs_ob) {
            cout << "Proxy::const Proxy&  operator= \n"; 
            //PyObject_SetItem( container.p, key.p, static_cast<Object>(rhs_ob).p );
            this->container = rhs_ob.container;
            this->key = rhs_ob.key;
            return *this; // allow daisy-chaining a = b = c etc, that's why we return const Object&
        }

        Object operator->() { 
            cout << "Proxy::Object operator->() \n"; 
            return Object{ PyObject_GetItem(container,key) }; 
        }
    };
    
    Proxy operator[] (const Object& key) {
        cout << "Object::Proxy operator[] \n"; 
        return Proxy{ p, key.p };
    }
    

    const Object* operator -> () const { 
        cout << "Object::const Object* operator -> \n"; 
        return this; 
    }
    
    Object* operator -> () { 
        cout << "Object::Object* operator -> \n"; 
        return this; 
    }        
};

int main()
{
    PyObject a=1,b=2,c=3;
    Object ob=Object(&a), idx=Object(&b), targ=Object(&c);
    
    #define DO(x) cout << "- - - - - - - - - - - - - - - - \n" #x "\n"; x;
    
    DO( ob[idx] = targ )

    PyObject d=4;
    Object idy=Object(&d);
    
    DO( ob[idx] = ob[idy] )

    DO( ob[idx] = ob[idy] = targ )
    
    cout.flush();
    ob[idx]->someMethod();
        
    PyObject* w = ob[idx]->p;
} 
