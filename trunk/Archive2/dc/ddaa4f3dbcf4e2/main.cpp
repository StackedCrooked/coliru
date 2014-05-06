#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct X{
    X(){cout << "X ctor" << endl;};
    X(const X& ){ cout << "X copy ctor" << endl; };
    X& operator= (const X& ){ cout << "X assignment " << endl; return *this; };
    
    X(X&& rhs){ cout << "X move ctor" << endl; };  
    X& operator= (X&& rhs){ cout << "X move assignment" << endl; return *this; };
    
    // const X&& ?!? - why? but allowed; remember Rule #1
    /* X(const X&& rhs){ cout << "const X move ctor" << endl; };  
    X& operator= (const X&& rhs){ cout << "const X move assignment" << endl; return *this; }; */
    
    /*explicit*/ X(int){ cout << "X NON-EXPLICIT ctor" << endl; };
    };
    
X strucX;                               // --- PRINT: X ctor

X ret()
{ return strucX; }

void foo(X&)
{cout << "Inside Lval" << endl;}

void foo(X const &)
{cout << "Inside const Lval" << endl;}

void foo(X&& param)
{
  cout << "Inside Rval" << endl;
  X anotherX = param; // Which ctor will it call?
}



int main()
{
  X x;                              // --- PRINT: X ctor
  foo(x);                           // --- PRINT: Inside Lval
  foo(10);                          // --- PRINT: NON-EXPLICIT and Inside Rval
  foo(ret());                       // --- PRINT: X copy ctor and Inside Rval
}

