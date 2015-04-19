#include <iostream>
#include <string>
#include <fstream>

using namespace std;


void readGameFile();

int main()
{
    readGameFile();
    return 0;
}


void readGameFile()
{
    ifstream infile;
    string s;
    string fileName;
    getline(cin,fileName);
    infile.open(fileName);
    if(infile.is_open())
    {
        cout << "It worked!"<<endl;
    }
    else
    {
        cout << "You messed up"<<endl;  
    }
}