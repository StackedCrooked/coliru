#include <iostream>
#include <string>

struct my_bool {
  my_bool(bool x) : value(x){}
  operator bool() const { return value; }
  char value;
};

void print(my_bool x) {
    std::cout << "bool: " << x << std::endl;
}

void print(std::string x) {
    std::cout << "string: " << x << std::endl;
}

int main()
{
    print("hello");
}
