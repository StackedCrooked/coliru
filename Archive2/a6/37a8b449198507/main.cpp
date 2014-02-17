// Outer/Inner block scopes example

// Derived from: http://www.cplusplus.com/doc/tutorial/namespaces/

#include <iostream>
using namespace std;

int main () 
{
  // Initialize two int variables in this outer scope of main()
  int x{10};
  int y{20};
  
  { // Inner block's scope begins here
      
    int x{50};  // new 'x' initialization ok, we're inside main()'s inner block here
    y = 50;     // assign new value to outer scope's 'y'
    
    cout << "\n inner block scope \n";
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    
  } // Inner block's scope ends here
  
  cout << "\n outer block scope \n";
  cout << "x: " << x << endl;
  cout << "y: " << y << endl;
  
}