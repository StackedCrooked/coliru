#include <iostream>
#include <memory>

using namespace std;

class Test {
 public:
  Test() {
    std::cout << "Construct Test instance..." << std::endl;
  }
  
  std::string GetValue() const {
    return "a value";
  }
  
 private:
   // Disallow copy and assign.
   Test(const Test& rhs);
   Test& operator= (const Test& other);
};

// Return a newly created Test instance.
auto_ptr<Test> GetPtr() {
  return auto_ptr<Test>(new Test());
}

// Use a test instance.
std::string Use(const Test& test) {
  return test.GetValue();
}

int main() {
   auto_ptr<Test> result = GetPtr();
   std::cout << "Test instance returns '" << Use(*result) << "'" << std::endl;
   return 0;
}