#include <iostream>
#include <fstream>
#include <limits>
#include <string> // for std::string
#include <array>  // for std::array

struct RecAbbo{
    std::string name;       // use std::string
	std::string surname;    // use std::string
	int games;
	int won;
	int same;
	int lost;
	int place;
	int money;
};

template<class It>              // represents an iterator (similar to a point)
void safe(It begin, It end) {   // begin is an iterator that point to the beginning and end point to the "past-the-end" element
    std::fstream out;           // added std:: prefix
	out.open("data.txt", std::ios::out);    // added std:: prefix
    for (It it = begin; it != end; ++it) {  // loops trough all the elements from beginning until before past the end
		out << (*it).name << " \n";         // (*it) is to get the element "pointed" by `it` which is an iterator
		out << (*it).surname << " \n";
		out << (*it).games << " " << (*it).won << " " << (*it).same << " " << 
		(*it).lost << " " << (*it).place << " " << (*it).money << "\n";
	}
}

int main(){
    std::array<RecAbbo, 100> arr;   // local instead of global
	safe(arr.begin(), arr.end());   // you pass the begin and end iterator
}