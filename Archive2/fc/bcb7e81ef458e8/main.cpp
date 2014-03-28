#include <ostream>
#include <string>

struct Entry{
  std::string name;
  int number;
};

std::ostream& operator<<(std::ostream& os, const Entry& e){
   return os << "{\"" << e.name << "\"," << e.number << "}";
}

int main()
{
  Entry a;
  a.name = "Alan";
  a.number = 12345;
}