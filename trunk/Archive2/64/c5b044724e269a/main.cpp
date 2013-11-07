#include <iostream>
#include <cmath>
using namespace std;
double T;
double V;
double WC(double T, double V);
void index(double WC(double T, double V));

int main(void)
{
    
    V = 5.0;
    T = -60.0;
    // declare a function pointer which accepts two doubles and returns a double
    double (*wcPtr)(double, double);
    
    // initialise function pointer
    wcPtr = &WC;
    
    cout << "Please enter your T followed by your V" << endl;
    
    // call function pointer
    index(wcPtr);
}
double WC(double T, double V)
{
    if(V>4.8)
        return 13.12+0.6215*T-11.37*pow(V,0.16)+0.3965*T*pow(V,0.16);
    else
        return T;
}
void index(double WC(double T,double V))
{
    if (WC(T,V)<=0&&WC(T,V)>=-25)
    {
        cout<<"Discomfort";
    }
    if (WC(T,V)<-25&&WC(T,V)>=-45)
    {
        cout<<"Risk of skin freezing (frostbite)";
    }
    if (WC(T,V)<-45&&WC(T,V)>=-60)
    {
        cout<<"Exposed skin may freeze within minutes";
    }
    if (WC(T,V)<-60)
    {
        cout<<"Exposed skin may freeze in under 2 minutes";
    }
}
