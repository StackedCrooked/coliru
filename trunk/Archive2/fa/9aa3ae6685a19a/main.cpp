#include <iostream>

#include <fstream>

#include <cstring>

using namespace std;

int main(){
   ifstream input;
   char fname[20], lname[20];
   input.open("text.txt");

   input.getline(lname, 20, ',');
   input.getline(fname, 20, ' ');
   cout << lname;
   cout << fname;

}