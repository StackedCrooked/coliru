#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>

using namespace std;

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
 
    // if particles decay once per second on average,
    // how much time, in seconds, until the next one?
    std::exponential_distribution<> d(1);
 
    std::map<int, int> hist;
    for(int n=0; n<10000; n++) {
        cout << n << ". " << gen<<endl;
    }
    for(auto p : hist) {
        std::cout << std::fixed << std::setprecision(3) 
                  << p.first/100.0 << '-' << (p.first+1)/100.0 <<
                ' ' << std::string(p.second/200, '*') << '\n';
    }
}