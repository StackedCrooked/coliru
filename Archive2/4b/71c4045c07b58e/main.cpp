#include <memory>
#include <map>

class Foo;

class Bar 
{
   std::map<int, std::unique_ptr<Foo>> myMap;
};

int main()
{
};