#include <iostream>
#include <cmath>
#include <iterator>
using namespace std;

float legge_oraria_moto_accelerato(float a[3])
{
    return a[2]*a[0] + 0.5*a[1]*a[0]*a[0];
}
int corri(float (f)(float array[3]), float (&arrays)[3][3])
{
    for(auto& row : arrays) cout << f(row) << '\n';
    return 0;
} 

int main() {}
