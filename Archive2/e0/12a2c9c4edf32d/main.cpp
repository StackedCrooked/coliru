#include <iostream>

class Base {
public:
    virtual int   func_1( int a )        { std::cout << "Base::func_1" << std::endl; return a; }
    virtual float func_2( int a, int b ) { std::cout << "Base::func_2" << std::endl; return a+b; }
    virtual float func_3( char a )       { std::cout << "Base::func_3" << std::endl; return (float)a; }
};

class Final : Base {
public:
    int   func_1( int a )     override { std::cout << "Final::func_1" << std::endl; return a+1000;     }
    float func_3( char a )    override { std::cout << "Final::func_3" << std::endl; throw;             }
};

Base* get_base(void* s) {
    return reinterpret_cast<Base*>(s);
}

template <typename T, T t>
struct trap;

template <typename R, typename... Args, R(Base::*t)(Args...)>
struct trap<R(Base::*)(Args...), t>
{    
    static R 
    call(void* s, Args... args)
    {
        try
        {
            return (get_base(s)->*t)(std::forward<Args>(args)...);
        }
        catch (...)
        {
            return std::is_integral<R>::value ? static_cast<R>(42) : static_cast<R>(3.14); 
        }
    }
};


#define TRAP(f)  & trap<decltype(&f), &f>::call

class Trampoline 
{
    using F1 = auto ( void* self, int a )         -> int;
    using F2 = auto ( void* self, int a, int b )  -> float;
    using F3 = auto ( void* self, char a )        -> float;
    
    struct Table {
        F1* fp_1;
        F2* fp_2;
        F3* fp_3;
    };
public:
    Table* table = new Table();
    
    void enable_f1() { table->fp_1 = TRAP( Base::func_1 ); }
    void enable_f2() { table->fp_2 = TRAP( Base::func_2 ); }
    void enable_f3() { table->fp_3 = TRAP( Base::func_3 ); }
};

int main()
{
    Trampoline trampoline;
    
    trampoline.enable_f1();
    trampoline.enable_f3(); 
    
    Final final();
    
    Base* pBase = static_cast<Base*>(&final);
    void* base_as_pvoid = (void*)pBase;
    
    // test
    int u    = trampoline.table->fp_1( base_as_pvoid, 2 );     std::cout << u << std::endl; // expect: 1002   (enabled and Final provides override)
    float v  = trampoline.table->fp_2( base_as_pvoid, 3, 5 );  std::cout << v << std::endl; // expect: 8      (enabled but no override)
    float w  = trampoline.table->fp_3( base_as_pvoid, 'x' );   std::cout << w << std::endl; // expect: -3.14  (enabled and Final provides override, which throws!)
}
