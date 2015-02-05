#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, const char * argv[]) {

ofstream fout;
ifstream fin;
string s = "Hello world!";

fout.open("test.txt");
if(fout.is_open())
{
fout<<s;
fout.close();
}
else
{
    cout<<"Error ";
}

fin.open("test.txt");

if(fin.is_open())
{

while(getline(fin,s))
{
    cout<<"here";
    cout<<s<<endl;
}

    fin.close();
}


return 0;
}