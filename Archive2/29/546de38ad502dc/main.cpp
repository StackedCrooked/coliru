#include <iostream>
#include <string>

template<class T>
class rule
{
    public:
       std::string rules;  
};

struct S { std::string ex; };

int main(int argc, char** argv) {

  rule<class myexpression> myexpression1;
  rule<class myexpression2> myexpression2;
  
  S S; // S is used as a type and as a variable name
  S.ex = "";
  
  myexpression1.rules = "hello";
  myexpression2.rules = "hello2";
  return 0;
}