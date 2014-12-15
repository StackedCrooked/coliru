#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Base {
   public:
      void doBaseWork() {}    
};

template <typename T>
class Derived: public Base<T> {
  public:
     void doDerivedWork()
     {
         doBaseWork();
     }
};

int main()
{
   Derived<int> d;
   d.doDerivedWork();
}
