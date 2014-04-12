#include <iostream>
using std::cout;

void A();
void B(int*);
void C(int*);

 void A (){

 int *t = new int[3];



 B(t);
 C(t);

 }

 void B(int *t){

 t[1]=10;
 }

 void C (int *t){
 cout <<t[1];  
 }
 
 int main() {
     A();
 }
 