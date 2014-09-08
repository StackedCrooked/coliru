#include <iostream>
#include <vector>

struct NonStack
{
private:
  NonStack() = default;
public:
  static NonStack* Create(){
    return new NonStack;
  }
};
NonStack a;  //complile ok. but i thought it couldn't compile.

int main()
{

    return 0;
}