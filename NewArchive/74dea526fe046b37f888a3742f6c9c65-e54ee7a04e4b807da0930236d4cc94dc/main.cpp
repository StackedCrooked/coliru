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

template<class T, T t>
class piece
{
    public:
    piece(){cout<<"piece "<<t<<"\n";}
};
template<int N>
using piece_int = piece<int, N>;

int main()
{
    // nullptr
   foo(nullptr);
   
   // raw string
   string test = R"(\n\n\n\n)";
   cout<<test<<"\n";
   
   // rvalue, lvalue
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
   
   
   // template alias : using
   piece_int<5>();
   
   return 0;
}
