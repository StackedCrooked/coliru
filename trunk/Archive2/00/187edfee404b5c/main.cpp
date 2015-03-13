#include <iostream> 
using namespace std;
class A { 
público:     
   A (): A (0) {cout << "En A ()" << endl;} 
   A (int i): A (i, 0) {cout << "En A (int i ) "<< endl;} 
   A (int i, int j) { 
      num1 = i; 
      num2 = j; 
      aver edad = (num 1 + nu m2) / 2; 
      cout << "En A (int i, int j) "<< endl;}   
private: 
   int num1; 
   int num2; 
   int media; 
};
int main () { 
   clase A a; 
   return 0; 
} 
