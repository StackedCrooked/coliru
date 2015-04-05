//arrayinput.h
#include <array>
#include <string>

class arrayelimination
{
    public:
        const static size_t limit = 7;
        arrayelimination();
        void inputArray();
        void displayArray();

    private:
        std::array < int , limit > store;
        int userinput;
};



//arrayinput.cpp
#include <iostream>
#include <array>
//#include "arrayinput.h"
using namespace std;

arrayelimination::arrayelimination() : store( {{0}} ) // **** initialise store to all zeroes
{
    //static array < int , limit> store; // **** remove this ****
}


void arrayelimination::inputArray()
{

    for ( size_t i = 0; i < store.size(); i++ )
    {
        cout << "Enter number between 10-100 for array box [" // **** avoid these magic numbers
        << i << "]: " ;
        cin >> userinput;
        //check if numbers is between 10-100
        if ( userinput >= 10 && userinput <= 100 ) // **** avoid these magic numbers
        {
            // *********************************************************
            bool duplicate = false ;
            for ( int check : store )
            {
                if ( check == userinput )
                    {
                        duplicate = true ;
                        break;
                    }
        }

        store[i] = duplicate ? 0 : userinput ;
        // *********************************************************
        }

        //output if number isn't between 10-100
        else
        store[i] = 0;

    }
}

void arrayelimination::displayArray()
{
    cout << "Your unique array numbers stored include...\n";
    //output all the unique numbers that the user inputted.
    for ( size_t j = 0;  j < store.size(); j++ )
    {
        //if the value is NOT 0, output.
        if ( store[j] != 0 ) // **** avoid these magic numbers
        {
            cout << "array[ " << j << " ] = " << store[j] << "\n";
        }
    }
}

int main()
{
    arrayelimination a ;
    a.inputArray() ;
    a.displayArray() ;
}
