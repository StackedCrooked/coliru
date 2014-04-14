#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
    vector<double> v;
    v.push_back(1.2);
    v.push_back(3.1);

    fill_n(&v[0], v.size(), 0.0);
    
    cout << "V contents: \n";
    
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << ", ";   
        
    }

    return 0;
}

