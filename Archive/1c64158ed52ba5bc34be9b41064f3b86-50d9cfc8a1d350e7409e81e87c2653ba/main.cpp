#include <iostream>
#include <vector>
 
struct TestDelete
{
  int integer;
  TestDelete(int i) : integer(i)
  {
    std::cout <<"TestDelete constructor for "<< integer <<"\n\n";
  }
  
  TestDelete(const TestDelete& rhs) : integer(rhs.integer) {
      std::cout << "TestDelete copy constructor for " << integer << "\n\n";
  }
  
  TestDelete(TestDelete&& rhs) : integer(rhs.integer) {
      std::cout << "TestDelete move constructor for " << integer << "\n\n";
  }
  
  ~TestDelete()
  {
    std::cout <<"TestDelete destructor for "<< integer<<"\n\n";
  }
};
 
int main () {
  
  std::cout << "\noriginal:\n\n";
  std::vector<TestDelete> pt;
  pt.push_back(TestDelete(1));
  pt.push_back(TestDelete(2));
  
  std::cout <<"\nimprovement:\n\n";
  
  std::vector<TestDelete> pt2;
  pt2.reserve(2);
  pt2.push_back(TestDelete(1));
  pt2.push_back(TestDelete(2));
  
  std::cout << "\nLet the desruction commence.\n\n";
 
  return 0;
}