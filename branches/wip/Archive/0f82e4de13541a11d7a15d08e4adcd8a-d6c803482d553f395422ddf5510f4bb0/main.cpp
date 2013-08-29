 
#include <iostream>
 class Base
 {
   public:
     void get();
 };


 class derived: public Base
 {
   public:
   void put()
   {
    std::cout << "This is a bad idea" << std::endl;
    
   }
 };
 

void Base::get()
{
static_cast<derived *>(this)->put();  
}


 int main()
 {
  derived d;
  d.get();
 
  return 0;
 }