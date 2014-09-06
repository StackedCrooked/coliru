#include <iostream>
bool out = false;
int addNumbers(int x, int y)
{
    int answer = x;
    answer = 1;
    //return x + y;
}

int main(){
  if(!out) {
    addNumbers(10, 20);
    std::cout << 1 << std::endl;
  }
  else {
    std::cout << 2 << std::endl;
  }
}