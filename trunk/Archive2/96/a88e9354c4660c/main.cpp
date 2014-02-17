// Outer/Inner block scopes example.
// Author: LLD!5DeRpYLOvE
// Derived from: http://www.cplusplus.com/doc/tutorial/namespaces/

#include <iostream>
using namespace std;

// The entry point for all C++ programs.
int main () 
{
  // Declare (and initialize) two int variables in this outer scope of main().
  int x{10};
  int y{20};
  
  cout << "\n Original outer scope values; \n";
  cout << "x: " << x << endl;
  cout << "y: " << y << endl;
  
  { // Inner block's scope begins here.
      
    int x{50}; // Here in main()'s inner block's scope, another new (and totally
               //  different) 'x' variable declaration is OK, since we're
               //  protected here inside the inner block from having
               //  an 'x' name clash occur within our program.
    y = 50;    // Also, assign a new value into the (outer scope's) 'y' variable.
    
    cout << "\n Inner block scope values; \n";
    cout << "x: " << x << endl;  // This is the inner 'x' value.
    cout << "y: " << y << endl;  // This is the 'y' value.
    
  } // Inner block's scope ends here, so does the lifetime of the inner 'x' variable.
  
  cout << "\n Final outer scope values; \n";
  cout << "x: " << x << endl;  // Outer 'x' value remains unmodified from it's initialization.
  cout << "y: " << y << endl;  // But 'y' was assigned a new value within the inner block.
  
}