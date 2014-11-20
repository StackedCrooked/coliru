#include <iostream>
using namespace std;
int main (void) {
int idade, maior, menor;
cout<<"escreva sua idade: ";
cin>>idade;
maior=idade-18;
menor=18-idade;
if(idade >=18){
cout<<"ja poderia tirar a sua habilitacao ha: ";
cout<<maior;
cout<<" anos";
}
else{
cout<<"so podera tirar a habilitacao ha: ";
cout<<menor;
cout<<" anos";
}
return 0;
}
