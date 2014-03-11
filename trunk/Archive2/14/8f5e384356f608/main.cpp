#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
        double monthlyPay(double principal, double yir, int years){
int exponent = 12*years;
double mir = yir/1200;
double a = 1+mir;
double b = 1/a;
double c = 12 * years;
double d = pow(b,c);
double e = 1-d;
double f = principal * mir;
double payment = f/e;
cout<<setprecision(2)<<fixed<< payment<< endl;
return payment;
 }
int main(){
 cout<<"Please enter the principal loan amount "<<endl;
double principal;
cin>>principal;
cout<<"Now enter the interest rate for one month "<<endl;
double yir;//yearly rate
cin>>yir;
cout<<"Lastly enter the number of years "<<endl;
int years;
cin>>years;

monthlyPay(principal, yir, years );
cout<<"Month     Pay   Total    Monthly    Principal     Total      Remaining"<
cout<<"                 Paid     Interest     Paid      Principal    Balance"<<
cout<<"                                                  Paid           "<< end
double totalPaid = 0;
double payment = monthlyPay(principal,yir,years);
double monthlyInterest=(yir/1200)*principal;
double principalPaid = monthlyPay(principal, yir, years) - monthlyInterest;
int months = years *12;
double totalPrincPaid;
 totalPrincPaid=totalPrincPaid+ totalPrincPaid;
double remainingBalance;
 remainingBalance=payment - principalPaid;
int i=0;
if (( (i <8) &&(i>months-8) &&(i<months)) ){
double totalPaid;
totalPaid= totalPaid+ payment;
int month = 0;
int w=10;
cout<<setw(w)<<setprecision(2)<<fixed<<month<<setw(w)<<monthlyPay(principal,yir
<fixed<<monthlyInterest<<setw(w)<<setprecision(2)<<fixed<<principalPaid<<setw(w)
remainingBalance;
i++;
month ++;
}
}