g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out#include<iostream>
#include<string.h>
using namespace std;
void input(char*a){


char scentence;
int br=0;
int n=10;

do{
    scentence=cin.get();
    if(scentence!='/0'){
        a[br++]=scentence;


    }
    if(br==n){
    char*p=a;
    a=new char[n+10];
    for(int i=0;i<n;i++){
    a[i]=p[i];
    }
    delete[]p;
    n+=10;
    }
}
    while(scentence!='/0');
}










char* niz(char*sentence,int symbol, int from){
   int a=strlen(sentence);
   if(from>a)return NULL;
   if(symbol>a-from)return NULL;


   char newsentence[symbol];
   int start=a-from;
int stsimbl=symbol+start;
  for(int i=0;i<symbol;i++){
  for(start;start<stsimbl;start++){
  newsentence[i]==sentence[start];
  }
  }
  return newsentence;








}
int main(){

    int symbol,from;
     char*scentence;
     input(scentence);
    //input(scentence);




cout<<"broi simvoli";
cin>>symbol;
cout<<"na4alen simvol";
cin>>from;


char*newscentence=niz(scentence,symbol,from);

delete []scentence;
delete []newscentence;
cout<<newscentence;





return 0;
}