#include<fstream>
#include<iostream>
 
using namespace std;
 
void prepare()
{
ofstream x("inputFile.txt");
x << 1234567 << endl;
}
 
int main()
{
int a;
 
// n.m - create the file first so we can read it later
prepare();
 
//create and open file
ifstream input;
input.open("inputFile.txt");
 
//read value of 5 from file and assign to a
input >> a;
 
//print value of a
cout << a << endl;
 
// system("PAUSE");
}
