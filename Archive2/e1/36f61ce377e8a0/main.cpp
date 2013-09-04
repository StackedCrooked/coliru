#include <iostream>
#include <vector> 
using namespace std;

int main() {
    using lbfgsfloatval_t = float;
    
    lbfgsfloatval_t * k_array = new lbfgsfloatval_t[100];
    for(int i = 0; i < 100; i++)
        k_array[i] = (lbfgsfloatval_t)i;
    
    vector<lbfgsfloatval_t> k_vector(k_array, k_array+100);
    
    cout << k_array[0] << " " << k_array[1] << " " << k_array[99] << endl;
    cout << k_vector[0] << " "<< k_vector[1] << " "<< k_vector[99] << endl;
}