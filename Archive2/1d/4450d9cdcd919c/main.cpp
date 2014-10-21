#include <iostream>
using namespace std;

template <typename T, T I>
class Test
{
public: 
  Test(T d=I):i(d){
    cout << "init i="<<d<<endl;
  }
  operator T(){return i;}
  T i;
};

int main()
{
    Test<int, 7> t;
}