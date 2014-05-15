#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <limits>

using namespace std;

struct RecAbbo{
    	char name[20];
		char surname[20];
		int games;
		int won;
		int same;
		int lost;
		int place;
		int money;
	}Abbo[100];
	
void safe(RecAbbo);

int main(){
	safe(Abbo);
	return 0;
}


void safe(RecAbbo&){
	fstream out;
	out.open("data.txt", ios::out);
	for (int i=0;i<100; i++){
		out << Abbo[i].name << "  \n";
		out << Abbo[i].surname << " \n";
		out << Abbo[i].games << " " << Abbo[i].won << " " << Abbo[i].same << " " << 
		Abbo[i].lost << " " << Abbo[i].place << " " << Abbo[i].money << "\n";
		
	}
}
