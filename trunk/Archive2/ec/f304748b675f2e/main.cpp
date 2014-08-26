/*
C++lesson.cpp
Aug 22, 2014
gauvey42684
*/
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
// variables
    double mpg, distance, gallons, pricepergallon, totalcost

        //output using insertiuon operator
        cout<<"Enter mpg"<<endl;

        //input using extraction operator
        cin>>mpg;

        cout<<"Enter Distance in miles"<<endl;
        cin>>distance;
        cout<<"Enter Price for one gallon of gas"<<endl;
        cin>>pricepergallon;
        //calculate gallons needed
        gallons=distance/mpg;
        //calculate total cost
        totalcost=gallons * pricepergallon;
        cout<<"Total Trip Cost: $"<<fixed<<setprecision(2)<<totalcost<<endl;
return 0;
}