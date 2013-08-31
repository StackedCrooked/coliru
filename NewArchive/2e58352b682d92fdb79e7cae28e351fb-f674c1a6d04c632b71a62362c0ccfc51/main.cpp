#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


int main()
{
    int hubsize = 2;
    int authosize = 3;
    vector<double> hub (hubsize, 1 / (double) hubsize);
    vector<double> oldhub (hubsize, 1 / (double) hubsize);
    vector<double> autho (authosize, 1 / (double) authosize);
    
    for (int iter = 0; iter < 7; iter++ ) {
        hub[0] = autho[0] + autho[1] + autho[2] / 2;
        hub[1] = autho[2] / 2;
        
        autho[0] = oldhub[0] / 3;
        autho[1] = oldhub[0] / 3;
        autho[2] = oldhub[0] / 3 + oldhub[1];
        
        oldhub[0] = hub[0];
        oldhub[1] = hub[1];
    }
    
    for (int i = 0; i < authosize; i++) {
        cout << autho[i] << "\t";
    }
    cout << endl;
   
    return 0;
}
