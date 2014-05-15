#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <limits>
#include <string>
#include <array>

struct RecAbbo{
    	std::string name;
		std::string surname;
		int games;
		int won;
		int same;
		int lost;
		int place;
		int money;
};

template<class It>
void safe(It begin, It end) {
    std::fstream out;
	out.open("data.txt", std::ios::out);
    for (It it = begin; it != end; ++it) {
		out << (*it).name << "  \n";
		out << (*it).surname << " \n";
		out << (*it).games << " " << (*it).won << " " << (*it).same << " " << 
		(*it).lost << " " << (*it).place << " " << (*it).money << "\n";
	}
}

int main(){
    std::array<RecAbbo, 100> arr;
	safe(arr.begin(), arr.end());
}