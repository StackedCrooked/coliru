#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct GameInfo
{
    std::string name;
	int home;
	int away;
	friend std::istream &operator>>(std::istream &is, GameInfo &g);
	friend std::ostream &operator<<(std::ostream &os, GameInfo &g);
};

std::istream &operator>>(std::istream &is, GameInfo &g) {
	std::getline(is, g.name);
	is >> g.home;
	is >> g.away;
	is.ignore();
	return is;
}

std::ostream &operator<<(std::ostream &os, GameInfo &g) {
	os << "Name: " << g.name << "\n" << g.home << " " << g.away << std::endl;
	return os;
}


int main()
{
	std::string str = "3\nSD Lancers\n33   55\nND Cats\n34   67\nSD Big Horn\n67   68\n";
	std::cout << str;
	std::istringstream stream(str); // you could use ifstream instead
	size_t size(0);
	stream >> size; // not really nescesasry with vectors but still...
	stream.ignore();
	std::vector<GameInfo> gv;
	for (unsigned int i = 0; i<size; ++i){
		GameInfo g;
		stream >> g;
		gv.push_back(g);
	}
    
    std::cout << "\n-----------------\n";

	for (auto& el : gv)
	{
		std::cout << el << "\n-----------------\n";
	}

	return 0;
}
