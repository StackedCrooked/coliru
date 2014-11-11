#include <cassert>
class A
{
public :
    virtual int foo ( ) const = 0 ;
} ;

class B : public A { } ;
class C : public A { } ;

class D : public B , public C
{
public :
    virtual int foo ( ) const { return 12 ; }
} ;
int main() 
{
  D d;
  B* b = & d;
  C* c = & d;
  A* ab = b;
  A* ac = c;
  assert ( ab == ac) ;
} 