include <iostream>

using namespace std;

int main()
{
    double height;
    double weight;
    double bmi;
    double height_meters;
    double weight_Kg;
    cout<<"Please enter your height(inches): "<<endl;
    cin>>height;
    cout<<"Please enter your weight(lbs): "<<endl;
    cin>>weight;
    height_meters=height/39.3701;
    weight_Kg=weight/2.20462;
    bmi=weight_Kg/(height_meters*height_meters);
    cout<<"Your BMI is: "<<bmi<<endl;
    cout<<"Your height in Meters is: "<<height_meters<< endl;
    cout<<"Your weight in Kilograms is: "<<weight_Kg<<endl;
    system("pause");
    return 0;
}