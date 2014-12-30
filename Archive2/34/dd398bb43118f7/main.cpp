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

        /*
         This is to handle ... = ob[a] = ob[b] = ... .  
         The compiler provides an automatic operator=, unless I provide one. 
         Even if I do '=delete' on it, it _still doesn't get deleted_. ARGH.
         
         The idea was that since Proxy contains a Proxy->Object conversion, 
         the compiler could process 'fooProxy = barProxy' as 'fooProxy = Object(barProxy)'. 
         If only I could eliminate this 'Proxy operator=', it would have to fallback onto the 'Object operator='
         
         But '=delete' doesn't actually delete the function. It just raises an exception if the function is accessed. 
         Which to me is WRONG. It should have been '=raise'. And I don't see any way to prevent this assignment= function.
        */
        Proxy&  operator= (const Proxy& rhs_ob) {
            cout << "Proxy::const Proxy&  operator= \n"; 
            this->container = rhs_ob.container;
            this->key = rhs_ob.key;
            return *this; // allow daisy-chaining a = b = c etc, that's why we return const Object&
        }

        Object operator->() { 
            cout << "Proxy::Object operator->() \n"; 
            return Object{ PyObject_GetItem(container,key) }; 
        }
    };
    
    /* 
     This overload is unnecessary, and is just for efficiency. 
     If ob is const, we know that we won't be doing ob[idx]=...
     And so we can bypass having to engage the proxy mechanism.
    */
    const Object  operator[] (const Object& key)  const { 
        cout << "const Object operator[] \n";
        return Object{ PyObject_GetItem( p, key.p ) }; 
    }

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
    
    DO( Object out = ob[idx]; )
    
    DO( ob[idx] = targ )

    PyObject d=4;
    Object idy=Object(&d);
    
    DO( ob[idx] = ob[idy] )

    DO( ob[idx] = ob[idy] = targ )
    
    cout.flush();
    ob[idx]->someMethod();
        
    DO( PyObject* w = ob[idx]->p; );
    
    DO( /* avoid "variable not used" warnings */ )
    cout << w;
    cout << &out;
} 
