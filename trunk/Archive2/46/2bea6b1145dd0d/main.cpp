#include <iostream>
#include <cmath>

using namespace std;

int neg(int a,int b){
    if (b%2==0){
        return 1;
    }else{
        return (-1);
    }
}

int main(int argc, char* argv[]){
    int sum=0;
    unsigned int n;
    n=0;
    sum=0;
    //cin >> n;
    n=atoi(argv[1]);
    while(n){
        sum+= neg(-1,n) * n;
        n--;
    }
    cout << sum << endl;

    return 0;
}