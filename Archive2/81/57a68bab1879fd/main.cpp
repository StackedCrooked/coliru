#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>

using namespace std;

struct mystruct {
    map<string, vector<string> > mymap;
};

const mystruct fillData() {
    mystruct s;
    s.mymap["a"].push_back("apple");
    s.mymap["a"].push_back("orange");
    return s;
        
}

void display(const mystruct& s , const list<string>& l) {
    list<string>::const_iterator it;
    for(it = l.begin(); it != l.end(); ++it){
       vector<string> v = s.mymap[*it];
    }
}
int main()
{
    list<string> l;
    l.push_back("a");
    mystruct s = fillData();
    display(s,l); 
    
}
