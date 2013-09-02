#include <iostream>
 
#define MAXCHANNELS 20000
#define N_USER_SCAN_LIST 200

int main()
{
    short iIndex = 0;
    short iOffset = 4;
    
    short iScanlist=(iIndex+(iOffset*MAXCHANNELS))/N_USER_SCAN_LIST;

    std::cout << iScanlist << '\n';
}