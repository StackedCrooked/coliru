#include <iostream>
#include <fstream>
#include <iomanip>
 
using namespace std;
 
int main ()
{
        //Declare variables pertaining to the 2D array containing all the temperature values
        const int ARRAY_HEIGHT = 21;
        const int ARRAY_WIDTH = 4;
        double temperatures[ARRAY_HEIGHT][ARRAY_WIDTH];
        double fahrenheit = 0;
       
        //Declare variables pertaining to the input & output files containing the temperature data
        ifstream infile(".\\Input\\fahrenheit.txt");
        ofstream outfile(".\\Output\\converted_temperatures.txt");
       
        //Declare variables pertaining to the formatting of the text inside of the output file
        int column_width;
       
        /*Fill in the fahrenheit values into the temperatures array. If file does not exist or don't have read permissions, file
        stream could not be opened.*/
        if(infile.is_open())
        {
                cout << "File opened successfully!!!. Reading data from file into array" << endl << endl;
                while(infile >> fahrenheit)
                {
                        for (int i = 0; i < ARRAY_HEIGHT; i++)
                        {
                                temperatures[i][0] = fahrenheit;
                        }
                }
                cout << "Displaying the fahrenheit temperatures below: " << endl;
                for(int i = 0; i < ARRAY_HEIGHT; i++)
                {
                        cout << (i+1) << ". " << temperatures[i] << endl;
                }
        }
        //Provide an error message in case the input file could not be found and opened
        else
        {
                cout << "File could not be opened." << endl;
        }
       
        /*Calculate the celsius, kelvin, and rankine values and place them in the 2nd, 3rd, and 4th columns,
        respectively, of the temperature array.*/
        for (int i = 0; i < ARRAY_HEIGHT; i++)
        {
                temperatures[i][1] = (5.0/9.0) * (temperatures[i][0] - 32.0); //Calculate the celsius equivalent of the fahrenheit value
                temperatures[i][2] = (temperatures[i][1] + 273.15); //Calculate the kelvin equivalent of the celsius value
                temperatures[i][3] = (9.0/5.0) * temperatures[i][2]; //Calculate the rankine equivalent of the kelvin value
        }
       
        //Prompt the user for formatting values
        cout << "How generously do you wish for the columns to be spaced out? (Minimum of 10): ";
        cin >> column_width;
        if (column_width < 10)
        {
                column_width = 10;
        }
       
        outfile << setw(column_width);
        outfile << "Fahrenheit" << "Celsius" << "Kelvin" << "Rankine" << endl;
        cout << setw(column_width);
        cout << "Fahrenheit" << "Celsius" << "Kelvin" << "Rankine" << endl;
        for (int i = 0; i < ARRAY_HEIGHT; i++)
        {
                outfile << setw(column_width) << fixed << setprecision(3) << temperatures[i][0] << temperatures[i][1] << temperatures[i][2] << temperatures[i][3] << endl;
                cout << "," << temperatures[i][0];
                cout << ", " << temperatures[i][1];
                cout << "," << temperatures[i][2];
                cout << "," << temperatures[i][3] << endl;
        }
       
        return 0;
}