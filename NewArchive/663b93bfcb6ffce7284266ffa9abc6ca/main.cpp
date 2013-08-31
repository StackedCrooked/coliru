// TrigMain_20130201A.cpp
// jk
// Trignomtric function examples.
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;

#define PI 3.141592654
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
    // var for atan
    long double var1 = 98.5;
    long double result = atanl(var1);

    // var for cos
    double var2 = 1.387;
    double result2 = cos(var2);

   // cosh()
    double var3 = 1.387;
    double result3 = cosh(var3);
    cout << "The hyperbolic cosine of " << var3;
    cout << " is " << result << endl;






// display
    cout << "The arctangent of " << var1;
    cout << " is " << result << endl;


    // cosh()
    cout << "The Hyperbolic Cosine of " << var3;
    cout << " is " << result << endl;

    // cosl()
    long double var4 = 1.387;
    long double result4 = cosl(var4);
    cout << "The (long) Cosine of " << var4;
    cout << " is " << result << endl;

    // sinh()
    double var5 = 1.387;
    double result5 = sin(var5);
    cout << "The Hyperbolic Sine of " << var5;
    cout << " is " << result5 << endl;

    // sinhl()
    double var6 = 1.387;
    double result6 = sin(var6);
    cout << "The (long) Hyperbolic Sine of " << var6;
    cout << " is " << result6 << endl;

    // sinl()
    long double var7 = 1.387;
    long double result7 = sinl(var7);
    cout << "The (long) Sine of " << var7;
    cout << " is " << result7 << endl;


// cos()
    //long double var8 = 1.387;
    long double var15 = 45.0;

    cout << setfill ('_') << setw (65) << "" <<endl;
    cout << "Radian measure:"; // << endl ;
    cout << endl <<"The Sine    of " << var15 << " Degrees = " << sin(var15);
    cout << endl <<"The Cosine  of " << var15 << " Degrees = " << cos(var15);
    cout << endl <<"The Tangent of " << var15 << " Degrees = " << tan(var15);
    cout << endl;



    cout << setfill ('_') << setw (65) << "" <<endl;
    cout << "Degree measure: "; //<< endl ;
    cout << endl <<"The Sine    of " << var15 << " Degrees = " << sin( var15 * PI/180);
    cout << endl <<"The Cosine  of " << var15 << " Degrees = " << cos( var15 * PI/180);
    cout << endl <<"The Tangent of " << var15 << " Degrees = " << tan( var15 * PI/180);
    cout << endl;


    cout << setfill ('_') << setw (65) << "" <<endl;

    double param = .5, result1;
    cout << "The ArcSine of    " << param << " is  " << asin (param) * 180.0 / PI << " degrees." << endl;
    cout << "The ArcCosine of  " << param << " is  " << acos (param) * 180.0 / PI << " degrees." << endl;
    cout << "The ArcTan of     " << param << " is  " << atan (param) * 180.0 / PI << " degrees." << endl;


    cout << setfill ('_') << setw (65) << "" <<endl;
    cout << endl <<"Press Enter to continue" << endl;

    cin.get();

    return 0;
}
