#include <iostream>
using namespace std;

/*class NUMS {
   //int* numbers;
   //int size;
  public:
  friend ostream& operator << (ostream& out, NUMS const& nums) {
       //for (int i = 0; i < size; ++i) out << nums.numbers[i] << " \n";
       return out << "what";
   } 
};*/

class A {};

class B : public A {
   //NUMS* numbers;
   public:
     friend ostream& operator << (ostream& out, B const& b) {
        //for (int i = 0; i < b.numbers->get_size(); ++i) out << b.numbers[i];
        return out << "cool";
     }
     friend ostream& operator << (ostream& out, A*  a) {
        //for (int i = 0; i < b.numbers->get_size(); ++i) out << b.numbers[i];
        return out << "cool";
     }
};

class C : public B {};

int main()
{
    A* a = new B();
    B b;
    cout << b;
}