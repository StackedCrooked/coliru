

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct data_t
{
    int a1;
	int a2;
	int a3;
	bool b;
};

int main()
{
	string file = "101,102,103,0" "\n"
		"1001,1002,1003,1" "\n"
		"2001.2002.2003,0";

	vector<data_t> v;
	istringstream sam(file);
	string row, s;
	while (getline(sam, row)) {
		istringstream is(row);
        data_t data;
        
		getline(is, s, ',');
		data.a1 = stoi(s) + 100;

		getline(is, s, ',');
		data.a2 = stoi(s) + 100;

		getline(is, s, ',');
		data.a3 = stoi(s) + 100;

		getline(is, s, ',');
		data.b = (bool)stoi(s);

		v.push_back(data);
	}


	for (auto &r : v) {
		cout << r.a1 << "," << r.a2 << "," << r.a3 << "," << r.b << endl;
	}

	return 0;
}
