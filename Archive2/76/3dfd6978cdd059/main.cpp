#include <iostream>
using namespace std;
class base1
{
    public:
        int a;
        virtual int reset(){
            a=0;
            return a;
        }
};

class derived1: public base1
{
    public:
        int b;
        int reset(){
            b=0;
            return b;
        }

};

template <class T>
class templateClass{
public:
    T *P;

    template <class U>
    templateClass& operator = (const templateClass<U> &b )
    {
        P = b.P;
        return *this;
    }
    

    void resetMyself(){
        P->reset();
    }
};

int main() {
    // your code goes here
    templateClass<base1> p;
    derived1 d;
    templateClass<derived1> q;
    q.P = &d;
    p = q;
    p.resetMyself();

    return 0;
}