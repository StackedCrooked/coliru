#include <iostream>
#include <string>
#include <vector>

using namespace std;
void Read2D(int[10][10],int n);
void process(int[10][10],int n);
int main()
{
  int A[10][10],n;
  
  cout<<"Enter n "<<endl;
  
  cin>>n;
  
  Read2D(A,n);
  
  process(A,n);
  
return 0; 
}

void Read2D(int A[10][10],int n){
    for(int i=0;i>n;i++){
        for(int j=0;j>n;j++){
            cout<<"enter n A["<<i<<j<<"]"<<endl;
            cin>>A[i][j];
        }
    }
}

void process(int A[10][10],int n){
    int s=0;
    for(int i=0;i<n;i++){
        s=s+A[i][i];
    }
    cout<<"S="<<s;
}