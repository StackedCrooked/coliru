#include <iostream>
#include <typeinfo>
#include <utility>

struct PyObject
{
    PyObject(int i_) : i{i_} {}
    int i;
};

struct Object
{
    // avoid implicit conversion
    explicit Object(PyObject* p_) : p{p_} { 
        std::cout << "Converting PyObject: " << p->i << std::endl; 
    }
    
    PyObject* ptr() const {
        return p;
    }  
private:
    PyObject* p;
};

struct Table {
    typedef PyObject*   (*getattrfunc)  (PyObject *, char *     );
    typedef PyObject*   (*getattrofunc) (PyObject *, PyObject * );
    typedef int         (*setattrfunc)  (PyObject *, char *     , PyObject *);
    typedef int         (*setattrofunc) (PyObject *, PyObject * , PyObject *);

    getattrfunc tp_getattr;
    setattrfunc tp_setattr;
    getattrofunc tp_getattro;
    setattrofunc tp_setattro;
} table{};

class Base {
public:
    Object  getattr( const std::string& s )                     { std::cout << "Base::getattr" << std::endl; return Object{ new PyObject(42) }; }
    int     setattr( const std::string& s, const Object& value ){ std::cout << "Base::setattr" << std::endl; return 666; }
};

class Final : public Base {
public:
    Object getattr( const std::string& s ){ std::cout << "Final::getattr" << std::endl; return Object{ new PyObject(43) }; }
} final{};

// helpers
template<typename T, typename U>       U&& mapperC2CXX( T&& t )         { return std::forward<U&&>(t); }
template<typename T>    const std::string& mapperC2CXX(       char* t ) { return new std::string(t); }
template<typename T>    const std::string& mapperC2CXX( const char* t ) { return new std::string(t); }
template<typename T>    const std::string& mapperC2CXX( PyObject*   p ) { return new Object{p}; }

template<typename T> 
struct Return {
    static T&& cvalue(T&& t) { return std::forward<T>(t); }
    static T&& cerr()        { return T(-1); }
};
template<>
struct Return<Object> {
    static PyObject* cvalue(const Object& ob)   { return ob.ptr(); }
    static PyObject* cerr()                     { return (PyObject*)nullptr; }
};

// function generator
template<typename Fc, Fc f, typename Target, Target target>
struct Generate;

template <  typename R      , typename ...Arg       , R(*f)(PyObject*, Arg...),
            typename RTarg  , typename ...TargArg   , RTarg(Base::*target)(TargArg...) >
struct Generate< R(*)(PyObject*, Arg...)    , f,
                 RTarg(Base::*)(TargArg...) , target >
{
    static Base* cxxbase_for(PyObject* pyob) {
        return (Base*)&final; // cheat for now!
    }
    
    static R call( PyObject* self, Arg... carg) 
    {
        try
        {
            RTarg r_cxx = (cxxbase_for(self)->*target) (mapperC2CXX<Arg>(carg)...);
            return Return<R>::cvalue(r_cxx);
        }
        catch (...)
        {
            std::cout << "CAUGHT" << std::endl;
            return Return<R>::cerr();
        }
    }   
};

#define BIND(c_slot, cxx_target) c_slot = & Generate< decltype(Table.c_slot), &c_slot,   decltype(&cxx_target), &cxx_target >::call;

int main()
{
    BIND( table.tp_getattr, Base::getattr );
    
    // test -- imagine C library fires this
    PyObject* self = (PyObject*)&final;
    PyObject* pyob = table.tp_getattr( self, (char*)"someattribute" );
    
    std::cout << pyob->i << std::endl;
}
