#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

int main(int argc, char ** argv){
    ifstream swapList (argv[1]);
	if (!swapList.is_open()){
		exit(1);}
	long int swap[64];
	char * temp;
	for(int i=0;i<atoi(argv[2]);i++){
		//getline(swapList,temp);
		//swapList.getline(temp,3,',');
		swapList >> temp;
		swap[i]=strtol(temp,NULL,16);
		cout << swap[i] << "\n";}
	return 0;
	}