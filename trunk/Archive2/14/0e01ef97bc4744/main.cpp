#include <fstream>
#include <string>

using namespace std;

void myFunction (string &fileName){
   fileName += ".txt";
   fstream file; 
   file.open(fileName, iostream::out);
   file << "This is my house, this is my home\n";
}

int main()
{
    string fn("test");
    myFunction(fn);    
}