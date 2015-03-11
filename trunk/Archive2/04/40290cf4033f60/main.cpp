#include <iostream>
using namespace std ;

int main() {;
int div;
int n;
int r;
cout<<"che numero devo controllare?"<< endl;
cin>>n;
r=n%div;
while (n>div) {
    if(r==0){
        cout<<" il numero non e' pari!" <<endl;
        div=n+10;
    }
    if(r==1){
        div=div++;
        
    }
}
if(n<div) {
    cout<<" fine!" <<endl;
}
else {
    cout<<" il numero e'primo!" <<endl;
}
