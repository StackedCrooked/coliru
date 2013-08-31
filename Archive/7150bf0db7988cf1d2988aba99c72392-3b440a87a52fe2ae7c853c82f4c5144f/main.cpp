class A {
public:
    virtual ~A(){}
};
class B : public A{};

int main() {
    A *a = new A();
    A *a2 = new B();
    
    B *derived = dynamic_cast<B *>(a);
    derived = dynamic_cast<B *>(a2);
}
