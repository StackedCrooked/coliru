#include <iostream>

using namespace std;




void convertWeight(double ounces, double grams, int &pounds, int &kilograms);
double output(double ounces, int pounds);

int main()
{
    double ounces;
    int pounds;

    char answer;

    do
    {
        cout << "Enter weight in pounds and ounces: " << endl;
        cin  >> pounds >>  ounces;
        cout << output(pounds, ounces) << endl;

        cout << "Do you want to test again (y/n)?: " << endl;

        cin >> answer;

    }
    while (answer == 'y' || answer == 'Y');

    return 0;
}

double output(double ounces, int pounds)
{
    double grams;
    int kilograms;

    convertWeight(ounces, grams, pounds, kilograms);

    cout << pounds << "pounds and " << ounces << "ounces = "
         << kilograms << "kilograms and " << grams << " grams."  << endl;


    return 0;

}

void convertWeight(double ounces, double grams, int &pounds, int &kilograms)
{
    kilograms = (pounds + ounces/16)/2.2046;
    grams = kilograms * 1000;
}