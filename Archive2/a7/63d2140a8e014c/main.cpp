#include <iostream>
#include <cmath>
#include <iomanip>

using std::cout; 
using std::endl; 
using std::cin; 

using std::fixed; 
using std::setprecision; 

int windchill(double, double); 

int main()
{ 
    double wind, temp; 
    
    cout<<"Please enter the wind speed: "; 
    cin>>wind; 
    cout<<"Please enter the temperature: "; 
    cin>>temp;
    
    while (temp>10) 
    { 
        cout<<"The temperature should be less than 10. Try again: "; 
        cin>>temp; 
    } 
    
    cout<<"The wind chill index is "<<setprecision(4)<<fixed<<windchill(wind,temp)<<endl;
    
    return 0; 
} 

int windchill(double v, double t)  // diba dapat double ung return type ?
{ 
    int w; // double din dapat 2
    w =(33-(((10*sqrt(v)-v+10.5)*(33-t))/23.1));
    return w; 
}