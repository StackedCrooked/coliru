#include<iostream>
using namespace std;
int main(){
    int a[100][100],b,c;
	cin>>b>>c;
	for(int i=0;i<b;i++){
		for(int j=0;j<c;j++){
			cin>>a[i][j];}}
	for(int i=0;i<b;i++){
		for(int j=0;j<c;j++){
			int f=a[0][j];
			a[0][j]=a[b-1][j];
			a[b-1][j]=f;
		}}
		cout<<endl;
	for(int i=0;i<b;i++){
		for(int j=1;j<c-1;j++){
			int d=a[0][j];
			a[0][j]=a[b-1][j];
			a[b-1][j]=d;}}
	for(int i=0;i<b;i++){
		for(int j=0;j<c;j++){	
cout<<a[i][j]<<" ";

}cout<<endl;}


return 0;}
