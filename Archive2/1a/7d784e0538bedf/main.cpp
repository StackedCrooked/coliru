#include <fstream>

template<class It>
int safe(double begin, double end){
    It iterator;
    fstream out;
    out.open("data.txt", ios::out);
	for (iterator = begin; iterator != end; ++iterator){
		out << (*It).name << " \n";         
		out << (*It).surname << " \n";
		out << (*It).games << " " << (*It).won << " " << (*It).same << " " << 
		(*It).lost << " "<< (*It).money << "\n";
	}
	out.close();
	return 0;