#include <stdio.h>

class ABC
{
  public:
     const int& a;
     ABC():a(43) { }
     void newfoo()
     {
           printf("NEWFOO %d",a);
     }
};
int main()
{
   ABC obj;
   obj.newfoo();
}