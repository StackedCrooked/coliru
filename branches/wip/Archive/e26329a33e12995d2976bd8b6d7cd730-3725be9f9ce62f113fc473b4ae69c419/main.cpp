#include <new>

struct Trial{
    const double a;
    Trial(double a_) : a(a_){}
};

struct MyClass : private Trial{
    MyClass(double a_) : Trial(a_), i(0) {};
    void wannaBeStrongGuaranteeMemberFunction(){
        MyClass old(i);
        bool failed = true;
        //... try to perform operations here
        if(failed) {
            this->~MyClass();
            new (this) MyClass(old);
        }
    }
    unsigned int i;
};

int main(){
    MyClass m1(1.);
    m1.wannaBeStrongGuaranteeMemberFunction();
}
