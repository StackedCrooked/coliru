#include <iostream>

using namespace std;

class BaseChannel{
  private:
  public:
   virtual ~BaseChannel(){};
   virtual void SayBoo( bool SelectAll)=0;
};

class gdbChannel: BaseChannel{
public:
 void SayBoo(bool SelectAll) {if (SelectAll) cout<<"boo";}
};

class UsesChannel{
public:
  BaseChannel * c;
};


int main()
{
   gdbChannel gc;
   UsesChannel uc;
   // uc.c = &gc; //cannot convert gdbChannel* to BaseChannel*
   uc.c = (BaseChannel*)&gc; // works
   uc.c->SayBoo(true);
    return 0;
}