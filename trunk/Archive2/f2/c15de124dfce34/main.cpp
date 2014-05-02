#include <iostream>
//#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    string lastName;
    string firstName;
    int sys, dia;
    
    // ****
    string input(
        "Smith Eleanore 110/73\n"
        "Jones Tom 200/78\n" );

    istringstream myFile( input );
    
    // ***
    //if( !myFile ) return 1;
    
    while( myFile >> lastName >> firstName >> sys &&
       myFile.ignore(10, '/') &&
       myFile >> dia )
    {
        if (sys <= 119 && dia <= 79)
    	cout << lastName << ", " << firstName << " has normal blood pressure at " << sys << "/" << dia << endl;
		
		else if (sys >= 120 && sys <= 139 || dia >= 80 && dia <= 89)
		cout << lastName << ", " << firstName << " has prehypertension at " << sys << "/" << dia << endl;

		else if (sys >= 140 && sys <= 159 || dia >= 90 && dia <= 99)
		cout << lastName << ", " << firstName << " has Stage 1 high blood pressure at " << sys <<"/"<< dia << endl;
			
		else 
		cout << lastName << ", "<< firstName << " has Stage 2 high blood pressure at " << sys <<"/"<< dia << endl;
    }
}

    
    