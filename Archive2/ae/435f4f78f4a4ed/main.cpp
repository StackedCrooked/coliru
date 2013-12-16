#include <iostream>

void swap(int &x, int &y){
  int tmp = x;
  x = y;
  y = tmp;
}

int main(){
  int a = 5;
  int b = 6;
  std::cout << a << " " << b << std::endl;
  swap(a,b);
  std::cout << a << " " << b << std::endl; 
}