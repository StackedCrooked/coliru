#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

struct noisy
{
    noisy() = default;
    noisy(const noisy&) { cout << "copy" << endl; } 
};

int main()
{
    map<int, noisy> m { {1, noisy{}}, {2, noisy{}} }; 
    
    cout << "subtle loop" << endl;
    for_each(m.begin(), m.end(), [](const pair<int, noisy>& p){
       cout << p.first << endl; 
    });
    
    cout << "fixed loop" << endl;
    for_each(m.begin(), m.end(), [](const pair<const int, noisy>& p){
       cout << p.first << endl; 
    });
    
}
