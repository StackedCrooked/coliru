#include <functional>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>


template<typename T0>
class delegate
{
    #define METHOD_RET void
    #define SCOPED_ARG(T, name) T::name
    #define METHOD_SIG(T) SCOPED_ARG(T, iterator), SCOPED_ARG(T, size_type), SCOPED_ARG(T, value_type)
    #define METHOD_SIG_DEF(T, Tfn) METHOD_RET (T::*Tfn)(METHOD_SIG(T))
    
    typedef void (*callable)(void* object_ptr, METHOD_SIG(T0));
    
    void* object_ptr;
    callable method_ptr;
    
    template<typename T, METHOD_RET METHOD_SIG_DEF(T, TMethod, void))>
    static void method_stub(void* object_ptr, METHOD_ARG1 _arg1, METHOD_ARG2 _arg2, METHOD_ARG3 _arg3)
    {
        T0* p = static_cast<T0*>(object_ptr, _arg1, _arg2, _arg3);
        return (p->*TMethod)(_arg1, _arg2, _arg3); // #2
    }
    
public:
    
    typedef METHOD_SIG_DEF(T0, TMethod);
    delegate() : object_ptr(0), method_ptr(0) { }
    
    template<typename T, METHOD_SIG(T, TMethod))>
    static delegate<T> from_method(T0* object_ptr)
    {
        delegate<T> d;
        d.object_ptr = object_ptr;
        d.method_ptr = &method_stub<TMethod>; // #1
        return d;
    }

    void operator()(METHOD_ARG1 _arg1, METHOD_ARG2 _arg2, METHOD_ARG3 _arg3) const {
        return (*method_ptr)(object_ptr, _arg1, _arg2, _arg3);
    }
    
    #undef METHOD_RET
    #undef SCOPED_ARG
    #undef METHOD_SIG
    #undef METHOD_SIG_DEF
};

typedef std::vector<int> vector_type; 
vector_type m_testVector;

int main() {
    // <vector_type::iterator, vector_type::size_type, const vector_type::value_type&> 
    //delegate<vector_type> _fn = 
    delegate<vector_type>::from_method<vector_type, &vector_type::insert>(&m_testVector);
    //delegate2.connect(m_testVector, &vector_type::insert);
    
    /*
    Delegate <const std::string&> delegate;
    A a;
    B b;
    
    delegate.connect(a, &A::print);
    delegate.connect(b, &B::print);

    delegate("hello");
    delegate("world");

    delegate.disconnect(a, &A::print);
    delegate("bye world");

    delegate.disconnect(b, &B::print);
    delegate("nobody there.");  // should not print anything
    */
}
