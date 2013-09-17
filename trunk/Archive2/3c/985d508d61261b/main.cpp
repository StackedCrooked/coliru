#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

map<string, int> lel;

vector<int> vec;

int main() {
    cout << "Filling map with values" << endl;
    
    for (int i = 0; i < 100; i++)
        vec.push_back(rand() % 10000);
    

    cout << "C++11 version: " << endl;
    
    for (vector<int>::iterator it : vec) {
        int dist = distance(it, vec.begin());
        cout << dist << ": " << endl;
    }
    
        
    
    
/*    lel["blörgh"] = 0;
    lel["swurpf"] = 38;
    lel["fourtytwo"] = 42;
    
    cout << "lel[\"blörgh\"] = " << lel["blörgh"] << endl
         << "lel[\"fourtytwo\"] = " << lel["fourtytwo"] << endl
         << "lel[\"swurpf\"] = " << lel["swurpf"] << endl;
*/



   return 0;
}
