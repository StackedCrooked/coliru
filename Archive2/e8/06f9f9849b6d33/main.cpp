#include <iostream>
using namespace std;

struct A {
    A(int aa){
        a = aa;
    }
    int a;
};


int main(void)
{
    A** a = new A*;
    *a = new A(10);
    cout << (*a)->a;
    
   return 0;
}
