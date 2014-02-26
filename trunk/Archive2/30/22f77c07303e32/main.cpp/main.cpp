#include <iostream>

using namespace std;

int main(){
    double a = 20;
    double b = 0.020;
    double c = 1000.0;

    double d = b * c;

    if(a < b * c)
        cout << "a < b * c" << endl;

    if(a < d)
        cout << "a < d" << endl;
        
    float af = 20;
    float bf = 0.020;
    float cf = 1000.0;

    double df = bf * cf;

    if(af < bf * cf)
        cout << "a < b * c" << endl;

    if(af < df)
        cout << "a < d" << endl;

    return 0;
}