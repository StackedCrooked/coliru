#include <map>
#include <iostream>

using namespace std;

int main()
{
map<string, string> aArray;
aArray["First"] = "William";
aArray["Second"] = "James";
aArray["Third"] = "Michael";
aArray["Forth"] = "Jayden";
aArray["Fifth"] = "Ashley";

for(std::map<string, string>::iterator it=aArray.begin();it!=aArray.end();++it){
    cout << it->first << endl;
    cout << it->second << endl;
}

}