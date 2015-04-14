#include <iostream>

class object {
  public:
  
  object() = default;
  object(const object&) = delete;
  object (object&&) = delete;
  
  int function() { return 42; }
    
  int val;
};

int main () {
    object *ptr = new object();
    
    // I'm not capturing an object, only a pointer to it
    auto lambda = [=] { object *ptr2 = ptr; };
    auto lambda2 = [=] {std::cout << ptr->function();};
}