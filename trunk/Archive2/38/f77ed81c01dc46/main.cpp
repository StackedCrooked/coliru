#include <iostream>

using namespace std; 

void sum1(int a, int b) { 
  a += b + 1;  
} 


int main() { 
  int *a = new int, *b = new int; 
  *a = 0; *b = 1; 
   cout << sum1(*a, *b) << endl;   // line 1 
    //sum2(*a, *b);   // line 2 
    //sum3(b, a);     // line 3 
    //sum4(&a, &b);   // line 4 
    //sum3(*a, *b);
    
    return 0;
}