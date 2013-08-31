#include <iostream>
#include <stdlib.h>
 
template<typename T1>
 
//Template for the max()
T1 max(T1 tx, T1 ty)
{
    return (tx>ty) ? tx : ty;
    
}
 
 
class Cents{
    
  private:
  int mCents;
  public:
  //Constructor
  Cents(int aCents)
  {
      mCents = aCents;
  }
  
  //Overloading the > operator
  /**Here Cents declares that the operator > is a friend and 
  then it enables it to do anything with its members**/
  /**Here it is better to opt for reference considering that w
   * we only need them to attend private service**/
  
  friend bool operator > (Cents &C1, Cents &C2)
  {
      //If C1 is greater than C2 then true
      return (C1.mCents > C2.mCents) ? true:false;
  }
  
};
 
 
int main()
{
    Cents a1(8),a2(3);
    
    if (a1>a2)
    {
        std::cout << "C1 is bigger than C2:" << (a1 > a2) ;
    }
}