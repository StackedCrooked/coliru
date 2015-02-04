#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

void check(bool isGood, string message, string fileName, string endLine);

void check(bool isGood, string message);

void getInt(int &var);



int main(){
  ofstream output;
  int n;
  double x;
  char ch;
  bool yes;
  string fileName;
  ifstream input;
  cout<<"Enter a name for the output file- ";
  cin>>fileName;
  output.open(fileName.c_str());
  check(output.good(),"Failure to open the file '",fileName,"'");
   input.open("input.txt");
check(input.good(),"Failure to open 'input.txt'");
    input>>n;
 while(input.good()){
    output<<n;
    input>>n;
  }
 cout<<"Enter an int- ";
  cin>>n;
  check(cin.good(),"'cin' has been disabled");
  cout<<"You entered the int "<<n<<endl;
  getInt(n);
  cout<<"You entered "<<n<<endl;
  /*
  getInt(n,2,10);
  cout<<"You entered "<<n<<endl;
  yes=getYorN(ch);
  cout<<"You entered '"<<ch<<"'\n";
  if(yes)
     cout<<"This means yes\n";
  else
    cout<<"This means no\n";
  x=0;
  getBool(yes);
  cout<<"You entered the bool "<<yes<<endl;
  getDouble(x);
  cout<<"You entered the double "<<x<<endl;

  */
}
void check(bool isGood, string message, string fileName,  string endLine) {

  if  (!isGood) {

    cerr<< message << fileName << endLine << endl;
    exit(1);
    }
}

void check(bool isGood, string message){

  check(isGood, message, "","");

}
  void getInt(int &var) {
    string empty;
     cout << "enter an int-"<<endl;
   cin >> var;
   while(!cin.good()){
      cin.clear();
       getline(cin, empty);
      cout << "You did not enter an int. Please enter an int: "<< endl;
      cin>>var;

	}

}