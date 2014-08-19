//inspired by http://stackoverflow.com/questions/25373587/how-to-compute-this-integral-using-c
#include <cmath>

double Sig1f = 3.14;
double Sig1i = 3.14;
double theta1 = 3.14;
double rho1 = 3.14;
double N1 = 3.14;

double dist1c(double z, double phi) 
{
    double firstdenom = ((Sig1f-Sig1i)/theta1*phi+Sig1i)*sqrt(2.0*M_PI);
    double exponent = -pow(z,2.0)/(2.0*pow((Sig1f-Sig1i)/theta1*phi + Sig1i,2.0));
    double result = pow(1.0/firstdenom,exponent);
    return result;
}
double dist1d(double z, double phi) 
{
    double firstdenom = ((Sig1f-Sig1i)/theta1*phi+Sig1i)*sqrt(2.0*M_PI);
    double exponent = -pow(z,2.0)/(2.0*pow((Sig1f-Sig1i)/theta1*phi + Sig1i,2.0));
    double result = pow(1.0/firstdenom,exponent);
    return result;
}
double dist1cprime(double z, double zp, double phi) 
{
    double result = 3.14;
    return result;
}
double dE1_integral(double z, double zp, double phi) 
{
    double firstdenom = pow(z-zp,1.0/3.0);
    double secondpart = dist1cprime(z, zp, phi);
    double result = 1.0/firstdenom*secondpart;
    return result;
}
double dE1(double z, double phi) 
{
   double max = z;
   double min = z-rho1*pow(phi,3)/24;
   double high = dE1_integral(z, max, phi);
   double low = dE1_integral(z, min, phi);
   double result = high-low;
   return result;
}
double dE1RMS_integral1(double z, double phi) 
{
    double result = dist1d(z,phi)*dE1(z,phi);
    return result;
}
double dE1RMS_integral2(double z, double phi) 
{
    double result = dist1d(z,phi)*dE1(z,phi);
    return result;
}
double dE1RMS(double phi) 
{
    double integral1max = 5*Sig1f;
    double integral1min = -5*Sig1f;
    double integral1high = dE1RMS_integral1(integral1max,phi);
    double integral1low = dE1RMS_integral1(integral1min,phi);
    double integral1 = integral1high-integral1low;
    
    double integral2max = 5*Sig1f;
    double integral2min = -5*Sig1f;
    double integral2high = dE1RMS_integral2(integral2max,phi);
    double integral2low = dE1RMS_integral2(integral2min,phi);
    double integral2 = integral2high-integral2low;
    
    double result = sqrt(integral1 - pow(integral2, 2));
    return result;
}
double kick1_integral(double phi) 
{
    double result = N1 * rho1 * dE1RMS(phi);
    return result;
}
double kick1() 
{
    double integralmax = theta1;
    double integralmin = 0;
    double integralhigh = kick1_integral(integralmax);
    double integrallow = kick1_integral(integralmin);
    double result = integralhigh - integrallow;
    return result;
}

#include <iostream>
int main() {
    std::cout << kick1();
    return 0;
}