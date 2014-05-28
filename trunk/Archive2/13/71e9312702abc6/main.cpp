#include <iostream>
#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
class Expression_Tree
{
  virtual void print(std::ostream&) = 0;
 /*irrelevant class logic*/
};

class Binary_Operator : public Expression_Tree
{
 public:
  void print(std::ostream& o);
 /*more irrelevant logic*/
};
/*stuff happens*/
#endif

void Binary_Operator::print(std::ostream& o) 
{
  /*do stuff*/
}

int main() {
    Binary_Operator{};
    std::cout << "WORKS!\n";
}