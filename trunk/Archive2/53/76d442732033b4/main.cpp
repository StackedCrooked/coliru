#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;
int main()
{
  string filename="Hello.txt";
  ofstream OutFile;
  OutFile.open(filename);
  if(OutFile.fail()) // check for successfully open ,
   {
    cout << "file named can not be found \n";
    exit(1);
   } 
    OutFile << "Hello, this is my output file";
    OutFile.close();
    system("pause");
    return 0;
}