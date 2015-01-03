#include <iostream>
 
using namespace std;

auto f1 = [] (auto a1, auto a2) {
    return a1+a2;
};



int main()
{ 
    auto u1 = f1(1, 2);
    
    cout << "u1: " << u1 << endl;
}