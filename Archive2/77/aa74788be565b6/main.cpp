#include <iostream>
#include <cstdlib>

class Base
{
};

template <typename NUM>
class Derived : public Base
{
public:
  Derived(NUM const &thing) : m_thing(thing) {}
  ~Derived() {}
private:
  NUM m_thing;
};

class AbstractFactory
{
public:
  virtual Base *construct() const = 0;
};


template <class Y>
class ConcreteFactory
{
public:
  Base* construct() const
  {
    return new Y();
  }
};

template<typename NUM>
class ConcreteFactory<Derived<NUM>> {
public:
  Base* construct() const
  {
    return new Derived<NUM>(rand());
  }
};

int main(int argc, char *argv[])
{
  ConcreteFactory<Base> baseFact;
  ConcreteFactory<Derived<int> > intFact;
  ConcreteFactory<Derived<double> > doubleFact;
  Base* a = baseFact.construct();
  Base* b = intFact.construct();
  Base* c = doubleFact.construct();
  delete c;
  delete b;
  delete a;
  
  std::cout << "Hello partial specialization!" << std::endl;
  
  return 0;
}