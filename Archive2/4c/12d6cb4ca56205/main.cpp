#include <stdexcept>

class my_error : public std::runtime_error {
public:
  explicit my_error(const std::string& what_arg) : std::runtime_error(what_arg) {};
};



#include <iostream>

int main()
{
  try {
    throw my_error("You can even pass a string here!");
  } catch (my_error e) {
    std::cerr << e.what();
  }
}