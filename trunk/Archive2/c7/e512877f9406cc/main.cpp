#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

template<typename _T>
class A{
        int _p;
        _T _k;
    public:
        A(int p, _T k):_p(p),_k(k){}
        void printK();
        void printP();
    };
    
int main()
{
    A<int> a(1,2);
}