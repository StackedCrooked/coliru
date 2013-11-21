#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct prop
{
    prop(string&& ss, int) : s(move(ss)), print{true} {
		cout << "rvalue" << endl;
	}
	
	prop(prop&& o) : s{move(o.s)}, print{o.print}
	{
		cout << "move" << endl;
	}
	
	prop(const prop& o) : s{o.s}, print{o.print}
	{
		cout << "copy" << endl;
	}
	
	
string s;	
const bool print;
};



int main(int argc, char** argv) 
{
    
    map<string, int> m {
		{string("ciao"), 1}
	};
    
    vector<prop> vvv;
    vvv.reserve(m.size());
	transform( make_move_iterator(begin(m)), make_move_iterator(end(m)), back_inserter(vvv), [](pair<string, int>&& p){
		return prop(move(p.first), p.second);
	} );
    
    return 0;
}