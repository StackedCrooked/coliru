#include<iostream>
#include<functional>

using namespace std;

int f(int n)
{  return 2*n; }

int g(int n)
{  return n+1; }

template<typename T>
function<int(int)> operator*(function<int(int)> f, const T &g)
{
  function<int(int)> g2=g; //this is encapsulated here so it is not
                           //necessary to repeat the same in main 
                           //for every functional composition
  return [=](int x){ return f(g2(x));};
}

int main()
{
  cout<<(f*g)(5)<<endl;
}
