#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isMotionMeaningful(string motion) //function should return true if it doesn't return false before that 
{
    for (int i = 0; i != motion.size(); i++) 
    {
        if (!isdigit(motion[i])) //this portion of the loop works in isolation
        {
            if ((motion[i] != 'W') && (motion[i] != 'w') && (motion[i] != 'S') && (motion[i] != 's') && (motion[i] != 'D') && (motion[i] != 'd') && (motion[i] != 'A') && (motion[i] != 'a') && (motion[i] != '/'))
            {
            return false; 
            }
        if (isdigit(motion[i]))
            {
            if ((motion[i] == '0') || (motion[i] == '1')) //if these digits are followed by a number or a slash
                {
                  int j = i + 1;
                  if (!isdigit(motion[j]) || motion[j] == '/')
                      {
                      return false;
                      }
                }
            }
       }        
   }     
   return true;
}   

int main ()
{
if (isMotionMeaningful("3w///10d//////////"))
    cout << "This case should work\n";
if (!isMotionMeaningful("z3w///10d//////////"))
    cout << "This case shouldn't work because it has a bad character\n";
if (!isMotionMeaningful("0w///10d//////////"))
    cout << "This case shouldn't work because it uses 0 by itself\n";
if (!isMotionMeaningful("2///10d//////////"))
    cout << "This case shouldn't work because it is a number is followed by a slash\n";

return 0; 
}