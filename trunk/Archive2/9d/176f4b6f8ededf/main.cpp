#include <iostream>
#include <fstream>

using namespace std;


int main()
{
    ofstream KineticEnergy;
	KineticEnergy.open("KineticEnergy.txt");
	KineticEnergy << "# Time KineticEnergy" << endl;
	KineticEnergy.close();
   cout << "Hello World" << endl; 
   
   return 0;
}
