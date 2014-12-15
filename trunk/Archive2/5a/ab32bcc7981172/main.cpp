#include <string>
#include <fstream>
#include <iostream>
 
 using namespace std;
int main()
{
    string filename = "example.123";
 
    fstream fs;
 
    fs.open(filename);
 
    if(!fs.is_open())
    {
       fs.clear();
       fs.open(filename, std::ios::out); //Create file.
       fs.close();
       fs.open(filename);
    }
 
    cout << std::boolalpha;
    cout << "fs.is_open() = " << fs.is_open() << '\n';
    cout << "fs.good() = " << fs.good() << '\n';
}