#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

class student {
private: 
    int id; 
    int n;  // no of- grades
    int A[200]; // array to hold the grades
public: 
    student(void);              // constructor
    void READ(void);          // to read from a file to be prompted by user;
    void PRINT(void);      // to write into an output file
    void showStudent();   //show the three attributes
    void REVERSE_PRINT(void);      // to write into output file in reverse order;
    double GPA(void);           // interface to get the GPA
    double FAIL_NUMBER(void); //interface to get the number of fails
};



void student::READ()
{

    ifstream inFile;
    ofstream outFile;
            string fileName;
            cout << "Input the name of your file" << endl;
            cin >> fileName;
            inFile.open(fileName.c_str());
            if (inFile.fail()) {
                cout << fileName << "does not exist!" << endl;
            }
            else
            {
                int x;
                inFile >> x;
                while (inFile.good()) 
                {
                    for(int i=0;i<200;i++)
                    {
                        A[i]=x;                 
                    }
                    inFile >> x;
                }
            inFile.close(); 
            }
}

int main()
{
     student a();
     a.READ();

}