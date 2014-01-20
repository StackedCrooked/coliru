#include <iostream>
#include <memory>
#include <utility>

using namespace std;

struct A {
    A(int&& n)                  { cout << "rvalue Construct overload, n=" << n << endl; }
    A(const int& n)             { cout << "lvalue Construct overload, n=" << n << endl; }
    //+2: unused
    A& operator=(int&& n)       { cout << "rvalue Assigning overload, n=" << n << endl; return *this; }
    A& operator=(const int& n)  { cout << "lvalue Assigning overload, n=" << n << endl; return *this; }
};
 
class B {
public:
    template<class T1, class T2, class T3>
    B(T1&& t1, T2&& t2, T3&& t3) :
        a1_(forward<T1>(t1)),
        a2_(forward<T2>(t2)),
        a3_(forward<T3>(t3))
    {}
    
private:
    A a1_, a2_, a3_;
};

template<class T, class... U>
unique_ptr<T> make_unique(U&&... u)
{
    return unique_ptr<T>(new T(forward<U>(u)...));
}
 
int main()
{   
    cout << 'A' << endl;
    auto pA(make_unique<A>(2));                 // rvalue
    int i = 1;
    pA = make_unique<A>(i);                     // lvalue
 
    cout << 'B' << endl;
    auto pB(make_unique<B>(i, i++, move(i)));   // rvalue, lvalue, rvalue
}