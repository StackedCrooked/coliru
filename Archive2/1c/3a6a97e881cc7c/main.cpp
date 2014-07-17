#include <iostream>
#include <string>

template<class T>
class rule
{
    public:
       std::string rules;  
};

int main(int argc, char** argv) {

  rule<class myexpression> myexpression;
  rule<class myexpression2> myexpression2;
  
  myexpression.rules = "hello";
  myexpression2.rules = "hello2";
  return 0;
}