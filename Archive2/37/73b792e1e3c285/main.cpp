#include <iostream>
#include <memory>

class A {
public:
    static int a;
    A(){ ++a; std::cerr << "A::A()" << std::endl; }
    ~A(){--a; std::cerr << "A::~A()" << std::endl;}
};

class B : public A {
public:
    static int b;
    B(){ ++b; std::cerr << "B::B()" << std::endl; }
    ~B(){ --b; std::cerr << "B::~B()" << std::endl; }
};

class C : public A {
public:
    static int c;
    C(){ ++c; std::cerr << "C::C()" << std::endl; }
    virtual ~C(){ --c; std::cerr << "C::~C()" << std::endl; }
};

class D : public C {
public:
    static int d;
    D(){ ++d; std::cerr << "D::D()" << std::endl; }
    ~D(){ --d; std::cerr << "D::~D()" << std::endl; }
};
 
int A::a  = 0;
int B::b  = 0;
int C::c  = 0;
int D::d  = 0;
 
int main()
{
    {
        std::shared_ptr<A> pAB1(new B);
        std::unique_ptr<A> pAB2(new B);
        A* pAB3 = new B;

        std::cout << "================================" << std::endl;

        std::shared_ptr<A> pAC1(new C);
        std::unique_ptr<A> pAC2(new C);
        A* pAC3 = new C;

        std::cout << "================================" << std::endl;

        std::shared_ptr<A> pAD1(new D);
        std::unique_ptr<A> pAD2(new D);
        A* pAD3 = new D;
        
        std::cout << "================================" << std::endl;

        std::shared_ptr<C> pCD1(new D);
        std::unique_ptr<C> pCD2(new D);
        C* pCD3 = new D;

        std::cout << "================================" << std::endl;

        std::cout << "A::a = " << A::a << std::endl;
        std::cout << "B::b = " << B::b << std::endl;
        std::cout << "C::c = " << C::c << std::endl;
        std::cout << "D::d = " << D::d << std::endl;
        
        std::cout << "================================" << std::endl;

        pAB1.reset();
        pAB2.reset();
        delete pAB3;

        std::cout << "================================" << std::endl;

        pAC1.reset();
        pAC2.reset();
        delete pAC3;

        std::cout << "================================" << std::endl;

        pAD1.reset();
        pAD2.reset();
        delete pAD3;
        
        std::cout << "================================" << std::endl;

        pCD1.reset();
        pCD2.reset();
        delete pCD3;
    }    
    
    std::cout << "A::a = " << A::a << std::endl;
    std::cout << "B::b = " << B::b << std::endl;
    std::cout << "C::c = " << C::c << std::endl;
    std::cout << "D::d = " << D::d << std::endl;
}