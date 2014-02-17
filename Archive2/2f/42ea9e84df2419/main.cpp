// Outer/Inner block scopes example.

// Derived from: http://www.cplusplus.com/doc/tutorial/namespaces/

#include <iostream>
using namespace std;

int main () 
{
  // Initialize two int variables in this outer scope of main().
  int x{10};
  int y{20};
  
  cout << "\n Original outer scope values; \n";
  cout << "x: " << x << endl;
  cout << "y: " << y << endl;
  
  { // Inner block's scope begins here.
      
    int x{50}; // Another (different) 'x' variable's initialization is ok, 
               //  since we're protected inside main()'s inner block here.
    y = 50;    // Also, assign a new value into the outer scope's 'y' variable.
    
    cout << "\n Inner scope values; \n";
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    
  } // Inner block's scope ends here, so does the lifetime of inner 'x'.
  
  cout << "\n Final outer scope values; \n";
  cout << "x: " << x << endl;
  cout << "y: " << y << endl;
  
}