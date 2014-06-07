#include <iostream>
#include <string.h>
#include <netinet/in.h>

using namespace std;

class A {
  int a;
  
  double func();
  
  virtual int vfunc();
  virtual double vfunc2();
  
};

int main()
{
    char buf[4];
    unsigned int tmp = htonl(4);
    memcpy(buf, tmp, 4);
    
    tmp = *reinterpret_cast<unsigned int*>(buf);
    
    tmp = ntohs(tmp);
    
    cout << "tmp? = " << tmp;
}
