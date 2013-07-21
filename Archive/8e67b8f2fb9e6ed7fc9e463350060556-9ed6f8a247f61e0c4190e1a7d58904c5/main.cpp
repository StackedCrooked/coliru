class C1 {
public:
    virtual void f() {  }
};

class C2 : public C1 { };

class C3 : public C2 {
public:
    virtual void f() { }
};

int main()
{
    C3 c;
    C1* p = &c;
    p->f();
}
