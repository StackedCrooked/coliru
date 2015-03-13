#include <iostream>
using namespace std;
class A{
public:    
   A(): A(0){ cout << "In A()" << endl;}
   A(int i): A(i, 0){cout << "In A(int i)" << endl;}
   A(int i, int j){
      num1=i;
      num2=j;
      average=(num1+num2)/2;
      cout << "In A(int i, int j)" << endl;}  
private:
   int num1;
   int num2;
   int average;
};
int main(){
   class A a;
   return 0;
}