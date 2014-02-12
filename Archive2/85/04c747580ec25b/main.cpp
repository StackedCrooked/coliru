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
void somekindoffunc()
{
    vector<string> A{"Alastor", "Eddy", "Noko"};
    vector<string> B{"gey", "a nerd", "a nurd"};
    vector<string> TheNextCarlSagan(3);
    
    for (int idx = 0; idx < 3; ++idx)
        TheNextCarlSagan[idx] = A[idx] +" is " + B[idx];
    
    for (int idx = 0; idx < 3; ++idx)
      cout << TheNextCarlSagan[idx] << endl;
}
    
// the entry point for all C++ apps
int main()
{
    somekindoffunc();
}
