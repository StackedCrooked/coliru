#include <iostream>
using namespace std;

template<typename T>
class SmartPtr
{
    public:
        explicit SmartPtr(T *p):m_p(p){cout<<"ctor"<<endl;}
        SmartPtr(const SmartPtr& p):m_p(p.m_p){cout<<"copy ctor"<<endl;}
        ~SmartPtr() { cout << "dtor" << endl; }

    private:
        T* m_p;
};

int main()
{
    SmartPtr<int> pt4 = SmartPtr<int>(new int);
}