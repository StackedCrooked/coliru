

#include <iostream>
#include <iomanip>
#include <stdarg.h>
#include <sstream>
#include <map>
#include <utility>
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[]) {

    	
	// REMARK
    unordered_map<string, double> umap1;
	umap1["key1"] = 0.16;
	umap1["key2"] = 0.07;
	umap1["pikey"] = 3.1415;
	cout << umap1["pikey"] << endl; // 3.1415	

	umap1["pikey"] = 3.15; // key exists, so value is updated
	umap1.insert(pair<string,double>("pikey", 3.0)); // insert syntax, if key exists, value is not updated
	umap1.insert(make_pair("pikey", 3.0));
	cout << umap1["pikey"] << endl; // still 3.15

	// LOOP keys
	for (auto x : umap1) {
		cout << x.first << " = " << x.second << endl;
	}
	for (unordered_map<string, double>::const_iterator pos = umap1.begin(); pos != umap1.end(); ++pos) {
		cout << (*pos).first << ' ' << (*pos).second << endl;
	}

	// MAP - elements stay in order, but can't access by index
	map<string, double> map1;
	map1["key1"] = 0.16;
	map1["key2"] = 0.07;
	map1["pikey"] = 3.1415;
	cout << map1["pikey"] << endl;
	for (auto x : map1) {
		cout << x.first << " = " << x.second << endl;
	}

	return 0;
}
