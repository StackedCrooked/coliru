#include <iostream>
#include <string>
#include <vector>
using namespace std;

double func(int k){
    if (k == 0){
        double sum = 0;
        for (int c = 0; c < 10000; c++){
            sum += c;
        }
        return sum;
    }
    k--;
    double sum0 = 0;
    double sum1 = 0;
    
    sum0 = _Cilk_spawn func(k);
    sum1 = func(k);
    _Cilk_sync;

    return sum0 + sum1;
}

int main()
{
    cout << func(4) << endl;
}
