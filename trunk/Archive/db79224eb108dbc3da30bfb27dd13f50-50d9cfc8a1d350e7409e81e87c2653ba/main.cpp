#include <iostream>
#include <string>
using namespace std;

int main(int argc, char ** argv){
	long int swap[64];
	string lll="00,01,02,0A,04,05,06,07,04";
	for(int i=0;i<lll.size()-1;i+=3){
		swap[i]=stoi(lll.substr(i+1,i+2),NULL,16);
		cout << swap[i] << "\n";}
	return 0;
	}