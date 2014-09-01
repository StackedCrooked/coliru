#include <fstream>
#include <iostream>

using namespace std;

int main()
    {
        ifstream infile;
        char c;
        infile.exceptions ( ifstream::failbit );

        try
        {
            infile.open("../Dose.c", ios::in);
            while (!infile.eof())
            {   
                c=infile.get();
                cout << c;
            }
            infile.close();

        }
        catch(ifstream::failure e)
        {
            cout << infile.eof() << " " << infile.fail() << " " << infile.bad() << " " << infile.good() ; 
            cerr << " Exception opening/reading/closing file\n";
        }
    return 0;
    }