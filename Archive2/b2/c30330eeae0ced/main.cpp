#include <iostream>
using namespace std;

double mean(int n, double *a){
double sum = 0;
for (int i=0; i<n; i++){
    sum += a[i];
    return sum/n;
}
}

int main(){
    double t[]={5, 5};
    cout << mean(2,t) << endl;
}