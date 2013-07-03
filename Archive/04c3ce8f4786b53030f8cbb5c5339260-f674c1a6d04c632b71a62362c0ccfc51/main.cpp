#include <future>
#include <iostream>

class Person{
public:
    void sum(int i){
        std::cout << i << std::endl;
    }
};

int main()
{
  int i=42;
  Person p;
  auto theasync=std::async([&p,i]{ return p.sum(i);});
}