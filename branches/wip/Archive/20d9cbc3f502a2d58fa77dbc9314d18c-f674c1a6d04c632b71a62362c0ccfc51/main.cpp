#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::string> names_type;

void get_names(names_type& names)
{
    names.push_back("a");
    names.push_back("b");
    names.push_back("c");
}

names_type get_names()
{
    names_type names;
    names.push_back("a");
    names.push_back("b");
    names.push_back("c");
    return names;
}

int main()
{
  names_type n1;
  get_names(n1);
  
  names_type n2 = get_names(); // for initlaization, more effecient than the above  
}