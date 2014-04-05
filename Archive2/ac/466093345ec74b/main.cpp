#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    cout << "Hi!" << endl;
    
    ofstream outfile;
    string sFilename = "glatisant.html";
    outfile.open(sFilename, ofstream::out);
    outfile.close();
}

