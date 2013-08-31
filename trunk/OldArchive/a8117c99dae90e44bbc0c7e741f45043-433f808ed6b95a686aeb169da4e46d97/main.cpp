class A {
public:
virtual int methodA() = 0;
virtual int methodB() = 0;
virtual int methodC() = 0;
};
 
class B { //B implements A.A() and A.B()
public:
int methodA() { return 0; }; 
int methodB() { return 0; };
};
 
class C : public A, public B {
public:
    using B::methodA;
    using B::methodB;
    int methodC() { return 0; }; //C implements A.C()
};
 
int main()
{
    C c;
    return c.methodA();
}