class AInterface {
    public:
        virtual void A()=0;
        virtual void B()=0;
        virtual void C()=0;
        virtual void C(char)=0;
        virtual void C(int)=0;
        virtual ~AInterface(){}
};

void AFunction(AInterface* i){}

class AClass {
    public:
        void A(){}
        void B(){}
        void C(){}
        void C(char){}
};

class MyClass : public AInterface, public AClass
{
public:
    using AClass::A;
    using AClass::B;
    using AClass::C;
    void C(int v) override {return AClass::C(v);}
};

int main() {
    MyClass b;
    AFunction(&b);
}