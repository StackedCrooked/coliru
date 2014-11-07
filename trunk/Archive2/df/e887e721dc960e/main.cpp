#include<iostream>
#include<fstream>
using namespace std;
int main() { ifstream ifile1,ifile2; ofstream ofile1, ofile2; ifile1.open("inFile1.txt"); ifile2.open("inFile2.txt"); int num1; int num2; cout<<"Reading Data..."<<endl; int i=0; while(ifile1 >> num1 >> num2); { cout <<endl<<num1<<endl<<num2; i++; } ifile1.close(); ifile2.close(); }