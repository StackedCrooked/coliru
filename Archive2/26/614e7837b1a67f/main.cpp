#include<iostream>
#include<functional>

using namespace std;

int f(int n)
{  return 2*n; }

int g(int n)
{  return n+1; }

struct F{}F;

function<int(int)> operator*(struct F, function<int(int)> g)
{ 
  return g;
}

function<int(int)> operator*(function<int(int)> f, function<int(int)> g)
{
  return [=](int x){ return f(g(x));};
}

int main()
{
  function<int(int)> f1=f, f2=g; //I want to encapsulate this step into operator*
  cout<<(F*f*g)(5)<<endl; //error in this line
}
