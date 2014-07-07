#include <iostream>

using namespace std;
class TCercle 
{
  public:
    virtual unsigned int aire(){return 5;};
};
int main()
{
    TCercle *r = new TCercle();  
    
    cout << r;
   return 0;
}
