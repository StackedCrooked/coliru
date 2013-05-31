#include <iostream>
#include <string>
using namespace std;

void foo(char* c)
{
    //static_assert(sizeof(c)==4,"input must not be null\n");
    cout << "char\n";
}
void foo(int c)
{
    cout << "int\n";
}


struct Base
{
virtual void some_func(float){
    cout<<"float\n";
    }
};
struct Derived : Base 
{
virtual void some_func(int){
    cout<<"int\n";
}
};

void bar(int&& c)
{
    cout<<"rval "<<c<<"\n";
}
void bar(int& c)
{
    cout<<"lval "<<c<<"\n";
    c = -c;
}

int x = 1.0;
int& getx()
{
    return x;
}

int main()
{
   foo(nullptr);
   string test = R"(\n\n\n\n)";
   cout<<test<<"\n";
   
   int&& a = 2;
   int c = 5;
   int& b = a;
   bar(c);
   bar(a);
   bar(b);
   cout<<"c = "<<c<<", b = "<<b<<", a = "<<a<<"\n";
   
   auto&& e = 1;
   cout<<"e rval:"<<is_rvalue_reference<decltype(e)>::value<<"\n";
   cout<<"e lval:"<<is_lvalue_reference<decltype(e)>::value<<"\n";
   
   bar(getx());
   cout<<"x = "<<x<<"\n";
   return 0;
}
