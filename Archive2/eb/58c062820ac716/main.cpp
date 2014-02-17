// inner block scopes
#include <iostream>
using namespace std;

int main () 
{
  int x = 10;
  int y = 20;
  
  { // Inner block's scope begins here
      
    int x;   // new 'x' declaration ok, inner scope.
    x = 50;  // assign value to inner 'x'
    y = 50;  // (re)assign new value to outer 'y'
    
    cout << "\n inner block scope \n";
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    
  } // Inner block's scope ends here
  
  cout << "\n outer block scope \n";
  cout << "x: " << x << endl;
  cout << "y: " << y << endl;
  
}