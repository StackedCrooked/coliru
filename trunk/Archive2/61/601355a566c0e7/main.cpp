#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string trim(string in){
    string out;
    int strBegin = in.find_first_not_of(" \t");
    if( strBegin == string::npos)
        return "";//nothing

    int strEnd = in.find_last_not_of(" \t");
    int strRange = strEnd - strBegin + 1;

    out = in.substr(strBegin, strRange);
    transform(out.begin(), out.end(), out.begin(), ::tolower);

    return out;
}

int main() {
    string temp;
    getline(cin, temp);

    temp = trim(temp);

for(int i=0; i<temp.length(); i++){
    cout<<temp.substr(i,i+1)<<" i: "<<i<<endl;
}
	return 0;
}