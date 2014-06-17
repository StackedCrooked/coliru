#include <iostream>
#include <random>

class MyProblem
{
public:
  int calculateMyProblem();
  MyProblem();

private:
  double _uniformRandNum;
  std::mt19937 _generator{1729};   // for 1729 I get ERROR: Expected a type specifier
  std::uniform_real_distribution<> _distribution{0,1}; // for both 0 an 1 i get ERROR: Expected a type specifier
  void generateUniformDistrNum();
  void calculateMeanDistance(); 
};

int main()
{
    MyProblem mp;
}
