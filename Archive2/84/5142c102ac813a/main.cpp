#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional> // std::mem_fn
using namespace std;

struct person{
    std::string name;
	bool likes_dogs;
	
	friend bool dog_lover(const person & p){
		return p.likes_dogs;
	}
};

int main() {
	vector<person> people = {{"Mary", true}, {"Stanley", false}};
	
	auto it = find_if(people.begin(), people.end(), [](const person& p) { return dog_lover(p); });
	
	return 0;
}