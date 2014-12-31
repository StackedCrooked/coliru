#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

using PyObject = string;

// Dummies for Python C-API functions
void      PyObject_SetItem( PyObject* pyob, PyObject* key, PyObject* value ) { 
    cout << "PyObject_SetItem                           " << *pyob << "[" << *key << "]=" << *value << endl; 
}

PyObject* PyObject_GetItem( PyObject* pyob, PyObject* key )                  { 
    cout << "PyObject_GetItem                           " << *pyob << "[" << *key << "]"            << endl;
    return new string( "item@" + *pyob + "[" + *key + "]" ); 
}

class Object {
public:
    PyObject* p;
    Object() {};
    
    Object(PyObject* _p) : p{_p} { cout << "Object{ " << (p==nullptr?0:*p) << " }" << endl; }
    
    void someMethod() { cout << "Object::someMethod()" << endl; }
    PyObject* ptr() { return p; }
    
    Object& operator= (const Object& rhs) {
        cout << "const Object& operator= " << endl;
        p = rhs.p;
        return *this;
    }

    class Proxy {
    private:
        PyObject* container;
        PyObject* key;
    
    public:
        // at this moment we don't know whether it is 'c[k] = x' or 'x = c[k]'
        Proxy( PyObject* c, PyObject* k ) : container{c}, key{k} { 
            cout << "Proxy(" << *c << ", " << *k << ")" << endl; 
        }
        
        ~Proxy(){ cout << "~Proxy()" << endl; }
        
        // Rvalue
        // e.g. fooObject = myList[5]
        operator Object() const {
            cout << "Proxy::operator Object() const             R-VALUE ACCESS" << endl; 
            return { PyObject_GetItem(container,key) };
        }
        
        // Lvalue
        // e.g. (something = ) myList[5] = foo
        Proxy&  operator= (const Object& rhs_ob) {
            cout << "Proxy& Proxy::operator= (const Object&)    L-VALUE ACCESS" << endl; 
            PyObject_SetItem( container, key, rhs_ob.p ); 
            return *this; // allow daisy-chaining a = b = c etc
        }

        /*
         This is to handle ... = ob[a] = ob[b] = ... .  
         The compiler provides an automatic 'Proxy operator=', unless I provide one. 
         
         My first idea is to eliminate this 'Proxy operator=', and hope that when the compiler encounters 
         'fooProxy=barProxy' it's overload resolution will notice Proxy provides conversion to Object, 
         and produce 'fooProxy=Object(barProxy)'.
         
         Unfortunately, the deleted function still participates in overload resolution. (Why??)
         And consequently the compiler produces a 'Proxy operator=' error instead.
         */
        Proxy&  operator= (const Proxy& rhs) {
            cout << "Proxy& Proxy::operator= (const Proxy&)     PROXY-PROXY" << endl; 
            cout << "getting rhs... " << endl;
            PyObject* val = rhs->ptr();
            cout << "... = " << *val << endl;
            
            PyObject_SetItem( container, key, val );            
            return *this; // allow daisy-chaining a = b = c etc
        }

        Object operator->() const { 
            cout << "Object Proxy::operator->()" << endl; 
            return { PyObject_GetItem(container,key) }; 
        }
    };
    
    /* 
     This overload is unnecessary, and is just for efficiency. 
     If ob is const, we know that we won't be doing ob[idx]=...
     And so we can bypass having to engage the proxy mechanism.
    */
    const Object  operator[] (const Object& key)  const { 
        cout << "const Object Object::operator[]            setting " << *p << "[" << *(key.p) << "] CONST-SHORTCUT" << endl; 
        return { PyObject_GetItem( p, key.p ) }; 
    }

    Proxy operator[] (const Object& key) {
        cout << "Proxy Object::operator[]                   creating proxy obj for " << *p << "[" << *(key.p) << "]" << endl; 
        return { p, key.p };
    }
    

    const Object* operator -> () const { 
        cout << "const Object* Object::operator -> " << endl; 
        return this; 
    }
    
    Object* operator -> () { 
        cout << "Object* Object::operator ->" << endl; 
        return this; 
    }        
};

int main()
{
    PyObject a="ob",b="idx",c="targ";
    Object ob=Object(&a), idx=Object(&b), targ=Object(&c);
    Object result;
    
    // std::endl flushes
    #define DO(x) cout << "- - - - - - - - - - - - - - - - \n" "EXECUTING: " #x << endl; x;
    
    DO( 
        PyObject pyob_in_const_ob = "pyob_in_const_ob";
        const Object const_ob(&pyob_in_const_ob); 
        //const_ob[idx] = targ; <-- can't assign to const obviously!
        result = const_ob[idx]; 
        )
    
    DO( Object out = ob[idx]; )
    
    DO( ob[idx] = targ )

    DO( auto x = ob[idx] )
      
    DO( 
        PyObject d="idy";
        Object idy=Object(&d);
        ob[idx] = ob[idy]; 
        )
    
    DO( ob[idx] = ob[idy] = targ )
    
    ob[idx]->someMethod();
        
    DO( PyObject* w = ob[idx]->p; );
    
    DO( /* avoid "variable not used" warnings */ )
    cout << w;
    cout << &out;
} 
