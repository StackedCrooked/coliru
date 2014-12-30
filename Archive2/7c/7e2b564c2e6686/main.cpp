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
            cout << "Proxy::Proxy&  operator= (const Object&) \n"; 
            
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
        Proxy&  operator= (const Proxy& rhs_ob) {
            cout << "Proxy::Proxy& operator= (const Proxy&) \n"; 
            PyObject_SetItem( container, key, rhs_ob.p );

            this->container = rhs_ob.container;
            this->key = rhs_ob.key;
            return *this; // allow daisy-chaining a = b = c etc
            /* Question: Do we really need to be setting the internal members of this proxy instance?
                Couldn't we just return rhs_ob?
                What if we had: uObj = (x[a]=y[b]) versus (x[a]=y[b]) = vObj? 
                Clearly both those cases will make further use of this proxy instance,
                So we must leave it in a usable state!
             */
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
    
    // std::endl flushes
    #define DO(x) cout << "- - - - - - - - - - - - - - - - \n" #x << endl; x;
    
    DO( Object out = ob[idx]; )
    
    DO( ob[idx] = targ )

    PyObject d=4;
    Object idy=Object(&d);
    
    DO( ob[idx] = ob[idy] )

    DO( ob[idx] = ob[idy] = targ )
    
    ob[idx]->someMethod();
        
    DO( PyObject* w = ob[idx]->p; );
    
    DO( /* avoid "variable not used" warnings */ )
    cout << w;
    cout << &out;
} 
