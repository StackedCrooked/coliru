#include <iostream>
#include <thread>
#include <vector>

using namespace std;

unsigned LongestOneSequence(unsigned int x)
{
    unsigned int result = 0;
    unsigned int tmp = 0;
    
    // Iterate over all bits
    while(x)
    {

            tmp = 0;
            // Look for a continuous sequence of 1
            while(x & 1)
            {
               x >>= 1;
               ++tmp;
            }
            // Update longest sequence
            if(tmp > result)
                result = tmp;
            // Shift if no 1 found
            if(tmp == 0)
                x >>= 1; 
    }
    return result;
}

int main(int argc, char** argv) {
    
    cout << LongestOneSequence(1) << endl;
    cout << LongestOneSequence(24) << endl;
    cout << LongestOneSequence(7) << endl;
    cout << LongestOneSequence(5) << endl;
    
    return 0;
}