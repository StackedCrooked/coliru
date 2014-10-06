#include <algorithm>
#include <vector>
#include <iostream>
#include <type_traits>

class State
{
public:
State() {}
State(State&&) {}
    State(State&) = delete;
    State& operator=(State&) = delete;
    State& operator=(State&&) = delete;
    ~State(){ std::cout << "abstract class" << std::endl;};
    
    virtual std::string nameOfState() const = 0;
    virtual int uniqueID() const = 0;
};

class MyState : public State
{
  int id{};
  std::string name{};
public:
  MyState() {}
  MyState(MyState&&) {}
  MyState& operator=(MyState& ms){return ms;}
  MyState& operator=(MyState&& ms) {return ms;}
  ~MyState(){ std::cout << "hi" << std::endl; }
  
  std::string nameOfState() const {return name;}
  int uniqueID() const {return id;}
};

int main(void)
{
    MyState ms{};
    std::cout << "hello" <<std::endl;
}


