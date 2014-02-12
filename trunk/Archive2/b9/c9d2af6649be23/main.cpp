// Tripcode@Home Rules!
//
// Author: LLD!5DeRpYLOvE

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;

// Proof m00t is a faggot.
void my_funky_func()
{
   // Initialize two source string vectors element's with three different strings each.
   vector<string> moot{"m00t", "moot", "m0ot"};
   vector<string> faggot{"faggot", "fagG0t", "faGgOt"};
   
   // Declare an empty target string vector (having a size of 3).
   vector<string> moot_is_faggot(3);

   // Concatenate the source vector's string elements together one by one, and assign
   //  that result into each of the target vector's elements one by one simultaneously.
   // (aka 'add them' lol :P )
   for (int idx = 0; idx < 3; ++idx)
      moot_is_faggot[idx] = moot[idx] + " is " + faggot[idx];

   // Stream the target vector's elements one by one to std::cout (console out) for output.
   for (int idx = 0; idx < 3; ++idx)
      cout << moot_is_faggot[idx] << endl;
}

// the entry point for all C++ apps
int main()
{
    my_funky_func();
}
