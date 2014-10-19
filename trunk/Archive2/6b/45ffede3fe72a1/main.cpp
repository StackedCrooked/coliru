#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(){

    bool magg=false;
	map<char, int> month={{'a',1},{'b',2},{'c',3},{'d',4},{'e',5},{'h',6},{'l',7},{'m',8},{'p',9},{'r',10},{'s',11},{'t',12}};
	string CF;

	cin >> CF;



	if(CF!="a"){
		int day, mesei, year;
		char mese;
	
		day = stoi(CF.substr(9));
		year = stoi(CF.substr(6));
		mese = CF.at(8);
		struct tm date = {0};
		
		mesei=month[mese];
		time_t current;
		time(&current);
		int secolo=date.tm_year-date.tm_year%100;
		if(secolo+year<date.tm_year){
			year=year+secolo;
		}else{
			year=year+(secolo-100);
		}



		date.tm_year = year;
		cout << endl << date.tm_year;
		date.tm_mon  = mesei-1;
		date.tm_mday = day;
		time_t normal = mktime(&date);
//		time_t current;
//		time(&current);
		long d = (difftime(current, normal) + 86400L/2) / 86400L;

		cout<<"You have: "<<d/365<<" years.\n";

		if(d/365>=16) magg=true;

	}else{
	



	}



	return 0;

}
