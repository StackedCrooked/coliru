class B{
public:
    virtual void f(int a){}
    virtual void f(){}
};
class A:public B{
public:
    virtual void f(int a){}
};
int main(){
A a;
a.f();
return 0;
}