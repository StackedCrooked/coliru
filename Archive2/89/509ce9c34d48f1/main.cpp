#include <iostream>
 
#define MAXCHANNELS 20000
#define N_USER_SCAN_LIST 200

int main()
{
    short iIndex = 173;
    short iOffset = 4;
    
    int absoluteIndex = iIndex+((int)iOffset*MAXCHANNELS);
    short iScanlist = absoluteIndex / N_USER_SCAN_LIST;
    short iElement = absoluteIndex % N_USER_SCAN_LIST;

    std::cout << iScanlist << '\n' << iElement << '\n';
}