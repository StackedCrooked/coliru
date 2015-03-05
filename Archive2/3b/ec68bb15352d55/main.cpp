#include <iostream>#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main(){
    string str="abcdbde";

	unordered_map<char,int> map;
    for(unsigned i=0; i<str.length(); i++){
    	m[str[i]]++;
    }
    cout << m['a'] << endl;
    cout << m['b'] << endl;
    cout << m['c'] << endl;
    cout << m['d'] << endl;
    cout << m['e'] << endl;
	return 0;
}
