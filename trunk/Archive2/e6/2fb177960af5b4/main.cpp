#include <iostream>
int main(){
double numbers[]={1.2,2.2,3.2,4.2};
double sum=0.0;
for(double number :numbers) 
{
sum+=number;
}
std::cout << sum;
}
