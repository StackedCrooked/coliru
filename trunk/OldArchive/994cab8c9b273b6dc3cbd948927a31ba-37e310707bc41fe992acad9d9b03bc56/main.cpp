#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    unsigned int vec[] = {5, 2, 3, 4, 6, 5, 6, 7, 8, 9, 8, 1};
    unsigned int n_elems = sizeof(vec)/sizeof(vec[0])-1;
    
    unsigned int threshold = 5;
    unsigned int model = 0;
    auto condition = [=](unsigned int i){return i < threshold;};
    replace_if( &(vec[0]), &(vec[n_elems+1]), condition, model); 
    
    auto compare = [=](unsigned int lhs, unsigned int rhs){return rhs == model;};
    stable_sort( &(vec[0]), &(vec[n_elems+1]), compare);
    
    for(auto& i : vec)
        cout << i << '\t';
    cout << endl;
}
