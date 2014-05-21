#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <limits>
#include <string>
#include <array>

using namespace std;

struct RecAbbo{
    	std::string name;
		std::string surname; 
		int games;
		int won;
		int same;
		int lost;
		int place;
		int money;
	}Abbo[100];

template<class It>
int safe(It begin, It end){
	fstream out;
	out.open("data.txt", ios::out);
	for (It it = begin; it != end; ++it){
		out << (*it).name << " \n";         
		out << (*it).surname << " \n";
		out << (*it).games << " " << (*it).won << " " << (*it).same << " " << 
		(*it).lost << " " << (*it).place << " " << (*it).money << "\n";
		
	}
	out.close();
	return 0;
}

template<class It>
int writetostruct(It begin, It end){
	fstream in;
	in.open("data.txt", ios::in);
	for (int i=0;i<100; i++){
		in >> std::skipws;  
		in.getline( Abbo[i].name, 20 ).ignore( std::numeric_limits< std::streamsize >::max(), '\n' ); 
		in.getline( Abbo[i].surname, 20 ).ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
		in >> Abbo[i].games >> Abbo[i].won >> Abbo[i].same >> 
        Abbo[i].lost >> Abbo[i].place >> Abbo[i].money;
    }
    in.close();
    return 0;
}
