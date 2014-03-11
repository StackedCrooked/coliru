#include<iostream>
using namespace std;
int devide(int x,int y){
    if(x<=y){
    return x;
    }else {return devide(x-y,y);
    }
}
main(){
       int x,y;
       cout<<"enter 2 numbers:"<<endl;
       cin>>x>>y;
       cout<<endl<<devide(x,y)<<endl;
       system("pause");
       }
