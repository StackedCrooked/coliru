#include <iostream>
#include <cmath>
using namespace std;

void beamMoment(double num1, double num2 ){
int l;
l=num1*pow(num2, 3)/ 12; // formula is i= height*base^3/12 
cout<<"the bean is equal to"<<l; // displaying the result

}
int main() {
double base =67; // declare default input
double height=45;
beamMoment(base, height);


return 0;
}