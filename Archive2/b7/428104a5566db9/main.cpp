#include <algorithm>
#include <atomic>
#include <functional>
#include <iomanip>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>



#define DBG(x) { using namespace std; cout << left << setw(30) << (#x) << (x) << endl; }

using namespace std;

auto main() -> int
{
    vector<vector<int>> p(10);

	for_each(begin(p),end(p),[i=1](vector<int>& v) mutable{
		v.resize(10);
		for_each(begin(v),end(v),[i,j=1](int& val) mutable{
			val = i*j++;
		});
		i++;
	});


	for_each(begin(p),end(p),[](vector<int>& v){
		for_each(begin(v),end(v),[](int& val){
			cout << setw(10) << right << val << " ";
		});
		cout << endl;
	});
	return 0;
}


