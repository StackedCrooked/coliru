#include <iostream>

class Base {
public:
    virtual int   func_1( void* self, int a )           const { std::cout << "Base::func_1\n"; return a; }
    virtual float func_2( void* self, int a, int b )    const { std::cout << "Base::func_2\n"; return a+b; }
    virtual float func_3( void* self, char a )          const { std::cout << "Base::func_3\n"; return (float)a; }
};

class Final : Base {
public:
    int   func_1( void* self, int a )   const  override { std::cout << "Final::func_1\n"; return a+1000;     }
    float func_3( void* self, char a )  const  override { std::cout << "Final::func_3\n"; throw;             }
};

using F1 = auto ( void* self, int a )         -> int;
using F2 = auto ( void* self, int a, int b )  -> float;
using F3 = auto ( void* self, char a )        -> float;

template<typename R, class...A> 
R (*trap_gen(R(*f)(A...)))(A...)
{
    static auto g = f;

    return [](A... a) 
    {
        try {
            return g(a...);
        } catch (...) {
            return std::is_integral<R>::value ? static_cast<R>(-42)
                                              : static_cast<R>(-3.14); 
        }
    };
}

class Trampoline {
    struct Table {
        F1 fp_1;
        F2 fp_2;
        F3 fp_3;
    };
public:
    Table table;
    
    void enable_f1() { table.fp_1 = trap_gen<>(Base::func_1); }
    void enable_f2() { table.fp_2 = trap_gen<>(Base::func_2); }
    void enable_f3() { table.fp_3 = trap_gen<>(Base::func_3); }
};

int main()
{
    Trampoline trampoline;
    
    trampoline.enable_f1();
    trampoline.enable_f3(); 
    
    Final final;
    
    // test
    int u    = trampoline.table.fp_1( (void*)&final, 2 );     std::cout << u; // expect: 1002   (enabled and Final provides override)
    float v  = trampoline.table.fp_2( (void*)&final, 3, 5 );  std::cout << v; // expect: 8      (enabled but no override)
    float w  = trampoline.table.fp_3( (void*)&final, 'x' );   std::cout << w; // expect: -3.14  (enabled and Final provides override, which throws!)
}