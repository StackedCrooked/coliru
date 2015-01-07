#include <iostream>
#include <functional>

class Base {
public:
    virtual int   func_1( int a )           const { std::cout << "Base::func_1\n"; return a; }
    virtual float func_2( int a, int b )    const { std::cout << "Base::func_2\n"; return a+b; }
    virtual float func_3( char a )          const { std::cout << "Base::func_3\n"; return (float)a; }
    
//    static int    func_1( void* self, int a )           { return to_base(self)->func_1(a);
//    static float  func_2( void* self, int a, int b )    { return to_base(self)->func_2(a, b);
//    static float  func_3( void* self, char a )          { return to_base(self)->func_3(a);
};

class Final : public Base {
public:
    int   func_1( int a )   const  override { std::cout << "Final::func_1\n"; return a+1000;     }
    float func_3( char a )  const  override { std::cout << "Final::func_3\n"; throw;             }
};

using F1 = std::function<int(Base *, int)>;
using F2 = std::function<float(Base *, int, int)>;
using F3 = std::function<float(Base *, char)>;

class Trampoline {
    struct Table {
        F1 fp_1;
        F2 fp_2;
        F3 fp_3;
    };
public:
    Table table;
    
    void enable_f1() { table.fp_1 = &Base::func_1; }
    void enable_f2() { table.fp_2 = &Base::func_2; }
    void enable_f3() { table.fp_3 = &Base::func_3; }
};

int main()
{
    Trampoline trampoline;
    
    trampoline.enable_f1();
    trampoline.enable_f2();
    trampoline.enable_f3(); 
    
    Final final;
    
    // test
    int u    = trampoline.table.fp_1( &final, 2 );     std::cout << u << std::endl; // expect: 1002   (enabled and Final provides override)
    float v  = trampoline.table.fp_2( &final, 3, 5 );  std::cout << v << std::endl; // expect: 8      (enabled but no override)
    float w  = trampoline.table.fp_3( &final, 'x' );   std::cout << w << std::endl; // expect: -3.14  (enabled and Final provides override, which throws!)
}