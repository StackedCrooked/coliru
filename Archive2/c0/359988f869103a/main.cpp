#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    string org_string = "REFRACTIVE LIGHT", fill_val;
	std::vector<string> keys;
	
	auto itersplit = [](const string &myword, string &token) ->bool {
		static istringstream word(myword);
		return (bool)(word >> token);
	};
	
	while (itersplit(org_string, fill_val)) {
		keys.emplace_back(fill_val);
	}
	
	for (auto key: keys)
		cout << key << endl;
	return 0;
}