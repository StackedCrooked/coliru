#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
string line;
ifstream IPFile;
int offset; 
char* search0 = "IPv4 Address. . . . . . . . . . . :";      // search pattern
        
system("ipconfig > ip.txt");

IPFile.open ("ip.txt"); 
if(IPFile.is_open())
{
   while(!IPFile.eof())
   {
   getline(IPFile,line);
   if ((offset = line.find(search0, 0)) != string::npos)
   {
//   IPv4 Address. . . . . . . . . . . : 1
//1234567890123456789012345678901234567890     
   line.erase(0,39);
   cout << line << endl;
   IPFile.close();
   }
}
}
return 0;
}