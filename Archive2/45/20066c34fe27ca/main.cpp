#include <iostream>
#include <string>
#include <vector>

using namespace std;

class B{
    
public:
    void f() {cout << "f() de B" << endl;}
    virtual void g() { cout << "g() de B" << endl;}
    virtual void h() = 0;
protected:
    int b
};

class D1: virtual public B
{
    public:
        void f() {cout << "f() de D1" << endl;}
        virtual void g() {cout << "g() de D1" << endl;}
    protected:
        int d1;
};

class D2 : virtual public B{
    
    public:
        void f(int i) {cout << "f(" << i << ") de D2" << endl;}
        virtual void h() {cout << "h() de D2" << endl;}
    
    protected:
        int d2;
};


class D3 : public D1{
    public:
        void g() {{cout << "g() de D3" << endl;}}
        void h() {cout << "h() de D3" << endl;}
    private 
        int d3;
};

class D4 : public D1, public D2
{
    private:
        int d4;
};

void f(B&b)
{
    cout << "F() externa" << endl;
    
    b.f();
    b.g();
    b.h();
};

int main()
{
}
