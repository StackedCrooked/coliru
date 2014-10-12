#include <iostream>
class myClass
{
  public:
   myClass (int x1 = 1, int y1 =1); //constructor
   myClass operator ++ (int);
   void increment();
   friend std::ostream& operator << (std::ostream& os, const myClass & m) {
       return os << m.x << '/' << m.y;
   }
  private:
   int x, y;
};

myClass::myClass (int x1, int y1)
{
  x = x1;
  y = y1;
}

myClass myClass::operator ++(int)
{
  myClass temp = *this;
  increment();
  return temp;
}
void myClass::increment() 
{
  x += y;
}
int main(){
    myClass a1(6,1); // x = 6, y =1;
    std::cout << a1++ << std::endl; // would expect output to be 6/1
    std::cout << a1 << std::endl; // would expect output to be 7/1
}