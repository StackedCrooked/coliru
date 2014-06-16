#include <iostream>
#include <random>

class MyProblem
{
public:
  int calculateMyProblem() { generateUniformDistrNum(); return 0; }

private:
  double _uniformRandNum;
  std::mt19937 _generator{1729};   // for 1729 I get ERROR: Expected a type specifier
  std::uniform_real_distribution<> _distribution{0,1}; // for both 0 an 1 i get ERROR: Expected a type specifier
  void generateUniformDistrNum();
  void calculateMeanDistance(); 
};

void MyProblem::generateUniformDistrNum() 
{
    _uniformRandNum = (double) _distribution(_generator); // ERROR, see below
}

int main()
{
    MyProblem mp;
    mp.calculateMyProblem();
}
