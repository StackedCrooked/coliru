#include <iostream>

struct file1 {
  file1() { std::cout<<"Inside constructor \n"; }
  file1(file1&&) {}
  ~file1() { std::cout<<"Inside destructor \n"; }
};


struct file2 {
  file1 cFunction() {
    file1 f1;
    return f1;
  }
};

int main() {
  file2 o1;
  file2 o2;
  file1 obj1 = o1.cFunction();
  file1 obj2 = o2.cFunction();
  
  return 0;
}