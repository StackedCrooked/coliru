#include <vector>
#include <string>
#include <set>
#include <iostream>
using namespace std;
int main(int argc,char*argv[])
{
std::set<int> set_1;
std::set<int> set_2;

set_1.insert(1);
set_1.insert(3);
set_1.insert(5);
set_2.insert(2);
set_2.insert(4);
    
    cout << "set_1:  ";
    for(auto i:set_1)
        cout << i << " " ;
    cout << endl << "set_2:  ";
    for(auto i:set_2)
        cout << i <<" ";
    cout << endl;
std::set<int>::iterator it1 = set_1.begin();
std::set<int>::iterator it2 = set_2.begin();
while ( (it1 != set_1.end()) && (it2 != set_2.end()) ) { 
    if (*it1 < *it2) {
        set_1.erase(it1++);
    } else if (*it2 < *it1) {
        ++it2;
    } else { // *it1 == *it2
            ++it1;
            ++it2;
    }   
}
// Anything left in set_1 from here on did not appear in set_2,
// // so we remove it.
// set_1.erase(it1, set_1.end());
    
    cout << "intersection:  ";
    for(auto i:set_1)
        cout << i <<endl;
return 0;
}
