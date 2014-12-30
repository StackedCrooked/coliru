#include <iostream>
#include <iomanip>
 
using namespace std;
int main()
{
    int TempTrip, VelMedia, TotPer;
    double TotSpent;
 
    cin>>TempTrip>>VelMedia;
 
    TotPer = VelMedia*TempTrip;
    TotSpent = TotPer /12.0;
    cout<<setiosflags (ios::fixed)<<setprecision(3)<<TotSpent<<endl;
 
 
 
 
 
 
    return 0;
}