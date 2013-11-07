#include<iostream>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;

long long int pow(long long int a, long long int n,long long int p) {
    std::cout << "pow("<<a<<", "<<n<<", "<<p<<")\n";
    long long int ret = 1;
    while(n) {
        if((n&1)== 1) ret=(ret*(a%p))%p;
        a*=a; n=n>>1;
        std::cout << "\ta: "<<a<<"\n";
    }
    return ret;
}
int main(){_
    int t;
    cin>>t;
    while(t--){
        unsigned long long int n,p,r;
        cin>>n>>p;
        r=p-1;
        if(n>=p){
            cout<<"0\n";
        }
        else{
            for(unsigned int i=p-1;i>n;i--){
                r=(r*pow(i,p-2,p));
                if(r>=p){
                    r=r%p;
                }

            }
            cout<<r<<"\n";
        }
    }   
    return 0;
}