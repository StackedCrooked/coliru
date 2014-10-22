#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>

using namespace std;

int main()
{
    random_device rd;
    mt19937 gen(rd());
 
    // if particles decay once per second on average,
    // how much time, in seconds, until the next one?
    exponential_distribution<double> d(1);
 
    map<int, int> hist;
    for(int n=0; n<2; n++) {
        cout << n << ". " << gen <<endl;
    }
    for(auto p : hist) {
        cout << fixed << setprecision(3) 
                  << p.first/100.0 << '-' << (p.first+1)/100.0 <<
                ' ' << string(p.second/200, '*') << '\n';
    }
}