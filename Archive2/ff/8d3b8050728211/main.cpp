#include <iostream>
#include <list>

struct MyStructure
{
    int somefield;
};

int main(int argc, char** argv) {

  std::list<MyStructure> my_list = { { 1 }, { 2 }, { 1 }, { 3 }, { 2 }, { 1 } };
  int somevalue = 2;
  my_list.remove_if( [somevalue](MyStructure s){ return s.somefield == somevalue; });
  
  for(auto& s : my_list)
      std::cout << s.somefield << " ";
  return 0;
}