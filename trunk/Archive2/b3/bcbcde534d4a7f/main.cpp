#include <iostream>
#include <string>
using namespace std;

struct A
{
  string s;

  A( const string& s = string() ):
  s( s.empty() ? string( "world" ) : s ) { }

  string hello() const
  { return string( "Hello " ) + s + "!"; }
};

struct B: public A
{
  using A::A;  // Inherit ALL of A's constructors

  string goodbye() const
  { return string( "Goodbye " ) + s + "!"; }
};

int main()
{
  string s;
  cout << "Whom do you wish to greet? ";
  getline( cin, s );

  B user( s );

  cout << user.hello() << endl;
  cout << user.goodbye() << endl;

  return 0;
}