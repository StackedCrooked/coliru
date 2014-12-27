struct I0              { virtual void f0() = 0; };
struct I1 : virtual I0 { virtual void f1() = 0; };
struct I2 : virtual I1 { virtual void f2() = 0; };
struct I3 : virtual I2 { virtual void f3() = 0; };

struct C0 :     virtual I0 { virtual void f0() {} };
struct C1 : C0, virtual I1 { virtual void f1() {} };
struct C2 : C1, virtual I2 { virtual void f2() {} };
struct C3 : C2, virtual I3 { virtual void f3() {} };

int main()
{
    C0().f0();
    
    C1().f0();
    C1().f1();
    
    C2().f0();
    C2().f1();
    C2().f2();
    
    C3().f0();
    C3().f1();
    C3().f2();
    C3().f3();
}