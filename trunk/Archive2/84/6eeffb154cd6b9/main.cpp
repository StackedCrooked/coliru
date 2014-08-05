#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    int phi_max[4];
    phi_max[0]=16; phi_max[1]=23; phi_max[2]=-22; phi_max[3]=-21;

    vector <int> rem_phi_max;
    int n_turn = 1;
    for(int i=(sizeof(phi_max)/sizeof(phi_max[0])-1); i>=n_turn; i--)
        rem_phi_max.push_back(abs(phi_max[i]));
        
    for(auto i : rem_phi_max){
        cout << i << '\t';
    }
    cout << endl;
}