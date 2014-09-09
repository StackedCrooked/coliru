#include <iostream>
#include <memory>

class MyClass {
  std::shared_ptr<int> mData;
public:
    MyClass() : mData(std::make_shared<int>(5)) {}
    void print() const { std::cout << *mData << std::endl; }
};

int main() {
  MyClass C;
  MyClass D(C);
  int *p = nullptr;
  C.print();
  D.print();
}