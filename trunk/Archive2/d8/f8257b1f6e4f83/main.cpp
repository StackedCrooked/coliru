#include <map>
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;


int main() 
{
    vector<int> a = {0, 1,2,3,4,5,6,7,8,9};
    
    cout << "for(auto i : a)"<<endl;
    for(auto i : a)
    {
        int & ref = i;
        ref = 5;
    }
    
    for(auto i : a) cout << i << " ";

    cout << endl<<"for(auto i = a.begin(); i != a.end(); i++)"<<endl;
    for(auto i = a.begin(); i != a.end(); i++)
    {
        int & ref = *i;
        ref = 5;
    }
    
    for(auto i : a) cout << i << " ";
}
