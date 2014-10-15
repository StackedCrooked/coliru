#include <vector>
#include <string>
#include <iostream>
#include <memory>

int main()
{
   std::vector<std::unique_ptr<std::string>> v;

   for(int i = 0; i < 10; i++)
     v.push_back(std::unique_ptr<std::string>(new std::string("Hello World")));

  // show the contents of the vector
  for(const std::unique_ptr<std::string>& s : v)
    std::cout << *s << " " << s->length() << '\n';
  std::cout << '\n';

  for(std::unique_ptr<std::string>& s : v)
    s.reset();
  v.clear();

  for(const std::unique_ptr<std::string>& s : v)
    std::cout <<*s << " " << s->length() << '\n';
  std::cout << "\nSize: " << v.size() << '\n';
}