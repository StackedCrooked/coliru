#include <vector>
#include <iostream>

using Values = std::vector<int>;

class Widget
{
protected:
  Values values_;
  mutable bool cached_ { false };
  mutable int sum_ { 0 };

public:
  Widget()
  {
    values_.push_back(0);
  }
  
  Widget(int value)
  {
    values_.push_back(value);
  }
  
  const Values& values() const
  {
    std::cout << "const call" << std::endl;
    
    return values_;
  }
  
  Values& values()
  {
    std::cout << "non-const call" << std::endl;
    
    cached_ = false; //values may change, cache may be invalid
 
    return values_;
  }
  
  void stuff() = delete;
  void stuff() const
  {
  }
  
  int sumOfValues() const
  {
    if (!cached_)
    {
      sum_ = 0;
      
      for(int value : values_)
      {
        sum_ += value;
      }
      
      cached_ = true;
      
      std::cout << "cache recalculated" << std::endl;
    }
    
    return sum_;
  }
};

int main (int argc, char** argv)
{
  std::vector<Widget> widgets {Widget{21}};
  
  std::cout << "Part One" << std::endl;
  
  for (const Widget & widget : widgets)
  {
    widget.stuff();
      
    std::cout << "size of values "
      << widget.values().size() << std::endl;
    
    std::cout << "sum of values - should recalculate - "
      << widget.sumOfValues() << std::endl;
  }
  
  std::cout << "Part Two" << std::endl;
  
  for (const Widget & widget : widgets)
  {
    widget.stuff();
      
    std::cout << "size of values "
      << widget.values().size() << std::endl;
    
    std::cout << "sum of values - should NOT recalculate - "
      << widget.sumOfValues() << std::endl;
  }
  
  std::cout << "Part Three" << std::endl;
  
  for (Widget & widget : widgets)
  {
    const_cast<const Widget &>(widget).stuff();
      
    std::cout << "size of values "
      << std::cout << widget.values().size() << std::endl;
    
    std::cout << "sum of values - should NOT recalculate - "
      << widget.sumOfValues() << std::endl;

   //play with this for fun
   widget.values().push_back(21);
    
    std::cout << "size of values "
      << std::cout << widget.values().size() << std::endl;
    
    std::cout << "sum of values - should recalculate - "
      << widget.sumOfValues() << std::endl;
  }
  
  return 0;
}
