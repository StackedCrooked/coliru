#include <iostream>           // std::cout
#include <vector>
#include <algorithm>

using namespace std;

class A {
    public:
    int a = 999;
    int b;
    unsigned c;
    void abc() { std::cout << "\n12314223\na = " << a << std::endl; }
    A() {std::cout << "CTOR " << this << endl;}
    ~A() { std::cout << "DTOR"<< this << endl; }
    void suicide() {delete this;}
    void foo() {a = 999;}
};


int main ()
{
    int count = 5;
    vector<A*> vec0;
    vector<A*> vec1;
    
    for (int i = 0; i < count; ++i)
    {
        A *a = new A;
        a->a = i;
        vec0.push_back(a);
    }
    
    vec1.push_back(move(vec0[0]));
    delete vec0[0];
vec0[0]->foo();
    cout << vec0[0]->a << endl;
    
    for (size_t i = 0; i < vec1.size(); ++i) 
    {
     cout << vec1[i] << endl;   
     vec1[i]->foo();
        
    }
  return 0;
}






















