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
      
    int x{50}; // After the inner block's scope begins, another new (and
               //  completely different) 'x' variable's initialization is
               //  OK, since we're protected here inside main()'s inner
               //  block from having an 'x' name clash in our program.
    y = 50;    // Also, assign a new value into the outer scope's 'y' variable.
    
    cout << "\n Inner block scope values; \n";
    cout << "x: " << x << endl;  // This is the inner 'x' value.
    cout << "y: " << y << endl;  // This is the outer 'y' value.
    
  } // Inner block's scope ends here, so does the lifetime of the new inner 'x'.
  
  cout << "\n Final outer scope values; \n";
  cout << "x: " << x << endl;
  cout << "y: " << y << endl;
  
}