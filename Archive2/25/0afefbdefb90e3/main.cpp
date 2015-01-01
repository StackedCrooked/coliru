#include <map>
#include <iostream>

int main()
{
    using namespace std;
    map<char*, char*> aArray;
    aArray["First"] = "William";
    aArray["Second"] = "James";
    aArray["Third"] = "Michael";
    aArray["Forth"] = "Jayden";
    aArray["Fifth"] = "Ashley";
    
    for(std::map<string, string>::iterator it=aArray.begin();it!=aArray.end();++it){
        cout << it << endl;
    }
}