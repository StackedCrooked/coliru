#include <iostream>
using namespace std;

int main()

{

    long kpm;
	long kills;
	long hours;
	long minutes;
	
	cout << "Kills per minute Calcer" << endl;
	cout << "Enter your kills" << endl;
	cin >>  kills;
	cout << "Enter hours played" << endl;
	cin >>  hours;
	cout << "Enter minutes played" << endl;
	cin >>  minutes; 
	
	kpm = kills  / (hours + (minutes / 60)) ; 
	
	cout << "Kills per minutes :" << kpm ;
	
	
	return 0; 

}