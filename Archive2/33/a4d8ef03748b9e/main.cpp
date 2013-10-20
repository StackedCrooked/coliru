#include <map>
#include <vector>
#include <list>
#include <functional>
#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace std::placeholders;


void print_person( pair<string, int> person) {
    cout << person.first << " " << person.second << "\n";
}



int main()
{
 
    map<string, int> person;  // name and age
    person["John"] = 35;
    person["James"] = 15;
    person["Norah"] = 40;
    
    for_each( person.begin(), person.end(), print_person );



    
}