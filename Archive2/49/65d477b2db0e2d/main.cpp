#include <iostream>
#include <string>
#include <vector>

int main(void){
char arr[][2]  =  {{0,1},{2,3}};
std::printf("%p\n",(arr+1));   

std::cout << (arr+1) << "\n";
std::cout << *(arr+1) << "\n";
return 0;
}