// inner block scopes
#include <iostream>
using namespace std;

int main () 
{
  int x = 10;
  int y = 20;
  
  {
    int x;   // ok, inner scope.
    x = 50;  // sets value to inner x
    y = 50;  // sets value to (outer) y
    
    cout << "\n inner block:\n";
    cout << "x: " << x << '\n';
    cout << "y: " << y << '\n';
  }
  
  cout << "\n outer block:\n";
  cout << "x: " << x << '\n';
  cout << "y: " << y << '\n';
}