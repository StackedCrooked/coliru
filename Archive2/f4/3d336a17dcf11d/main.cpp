#include <cstddef>
#include <iomanip>
#include <iostream>

using namespace std;

void stringOutput(int dayNumber, double *ptrTemperatures);

int main()
{
    int dayNumber;
    double fahrenheit = 0;
    double cTemperature = 0;
    const double MAXIMUM_TEMPERATURE = 60;// constants for mix/max
    const double MINIMUM_TEMPERATURE = -90 ;
    const int MAXIMUM_DAYS = 365;
    const int MINIMUM_DAYS = 1;
    double *ptrTemperatures = NULL;

    cout << "How many days would you like to enter? ";
//    dayNumber = myValidation::GetValidInteger(MINIMUM_DAYS, MAXIMUM_DAYS);
    try
    {
        ptrTemperatures = new double[dayNumber];
    }
    catch(exception e)
    {
        cout << "Failed to allocate memory: " << e.what() << endl;
    }
    cout << "\n\nTEMPERATURE REPORTER\n____________________________\n Please Enter the temperature for each day.";

    for(int dayCount = 0; dayCount < dayNumber; dayCount++){
        cout << "Celsius Temperature for Day " << (dayCount + 1) << ": ";
//        ptrTemperatures[dayCount] = myValidation::GetValidDouble(MINIMUM_TEMPERATURE, MAXIMUM_TEMPERATURE);
    }
    stringOutput(dayNumber, ptrTemperatures);



    delete[] ptrTemperatures;
    return 0;
}//end main

    void stringOutput(int dayNumber, double *ptrTemperatures)
    {
        cout << "DAILY TEMPERATURE REPORT\n__________________________________-\n\n";
        for(int dayCounter = 0; dayCounter < dayNumber; dayCounter++)
        {
//            cout << "Day " << dayCounter << (dayCounter+1) << setw(10) << celsiusToFahrenheit(ptrTemperatures[dayCounter]) << (char(248)) << "F"
//                << setw(10) << ptrTemperatures[dayCounter] << (char(248)) << "C" << endl;
        }
    }