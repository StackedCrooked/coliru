#include <iostream>

class A;

typedef int (A::*memFun)();

class A
{
    int P(){return 1;}
    int Q(){return 2;}
    int R(){return 3;}
    
    int Z(memFun f1, memFun f2)
    {
        return f1() + f2();
    }
public: 
    int run();
};

int A::run()
{
    return Z(P, Q);
}

int main()
{
    A a;
    cout << a.run() << endl;
}
