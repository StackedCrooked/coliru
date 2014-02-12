#include <iostream>
#include <map>
#include <set>

using namespace std;

struct foo
{
  foo(int n):n(n){}
  
  foo(const foo&  x):n(x.n){cout<<"const lvalue ref copy ctor\n";}
  foo(      foo&  x):n(x.n){cout<<"lvalue ref copy ctor\n";}
  foo(const foo&& x):n(x.n){cout<<"const rvalue ref move ctor\n";}
  foo(      foo&& x):n(x.n){cout<<"rvalue ref move ctor\n";}
  
  bool operator<(const foo& x)const{return n<x.n;}
  int n;
};

int main()
{
  cout<<"set\n";
  set<pair<int, const foo>> s;
  s.insert(make_pair(0,foo(0))); 

  cout<<"map\n";
  map<pair<int, const foo>,int> m;
  m.insert(make_pair(make_pair(0,foo(0)),0)); 
}
